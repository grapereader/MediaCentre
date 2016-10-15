#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#define SESSION_COOKIE "vmc-session"
#define SESSION_TOKEN_LENGTH 16
#define MAX_SESSION_AGE 12*60*60

#include <vector>
#include <memory>
#include <mutex>

#include "HTTPHeaders.h"
#include "Session.h"

namespace vmc
{
    class SessionManager
    {
    public:
        std::shared_ptr<Session> getSession(std::string const &sessionId);
        std::shared_ptr<Session> createSession();
    private:
        std::vector<std::shared_ptr<Session>> sessions;
        std::mutex sessionsMutex;
    };

    namespace session
    {
        std::shared_ptr<Session> init(SessionManager &sessionManager, HTTPHeaders const &requestHeaders, HTTPHeaders &responseHeaders);
    }
}

#endif
