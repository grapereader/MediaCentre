#include "SessionManager.h"

#include "String.h"

namespace vmc
{
    std::shared_ptr<Session> SessionManager::getSession(std::string const &sessionId)
    {
        this->sessionsMutex.lock();
        std::shared_ptr<Session> session;
        for (auto it = this->sessions.begin(); it != this->sessions.end();)
        {
            if (it->get()->getAge() > MAX_SESSION_AGE)
            {
                it = this->sessions.erase(it);
                continue;
            }
            else if (it->get()->getSessionId() == sessionId)
            {
                session = *it;
            }
            it++;
        }
        this->sessionsMutex.unlock();

        return session;
    }

    std::shared_ptr<Session> SessionManager::createSession()
    {
        auto session = std::shared_ptr<Session>(new Session(string::random(SESSION_TOKEN_LENGTH)));
        this->sessionsMutex.lock();
        this->sessions.push_back(session);
        this->sessionsMutex.unlock();
        return session;
    }

    namespace session
    {
        std::shared_ptr<Session> init(SessionManager &sessionManager, HTTPHeaders const &requestHeaders, HTTPHeaders &responseHeaders)
        {
            std::string sessionId = "";

            if (requestHeaders.exists("Cookie"))
            {
                std::string cookieString = requestHeaders.get("Cookie");
                auto cookies = string::split(cookieString, ";");
                for (auto it = cookies.begin(); it != cookies.end(); it++)
                {
                    std::string cookie = string::trim(*it);
                    auto cookieBits = string::split(cookie, "=", 1);
                    if (cookieBits.size() >= 2)
                    {
                        std::string name = cookieBits[0];
                        if (name == SESSION_COOKIE)
                        {
                            sessionId = cookieBits[1];
                        }
                    }
                }
            }

            if (sessionId.length() > 0)
            {
                auto session = sessionManager.getSession(sessionId);
                if (session) return session;
            }

            auto session = sessionManager.createSession();
            responseHeaders.put("Set-Cookie", std::string(SESSION_COOKIE).append("=").append(session->getSessionId()));
            return session;
        }
    }
}
