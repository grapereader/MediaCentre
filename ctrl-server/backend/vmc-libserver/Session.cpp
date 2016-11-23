#include "Session.h"

#include <stdint.h>
#include <exception>

namespace vmc
{

    Session::Session(std::string const &sessionId)
    {
        this->sessionId = sessionId;

        this->createdTime = std::time(nullptr);
    }

    std::time_t Session::getAge() const
    {
        return std::time(nullptr) - this->createdTime;
    }

    std::string const &Session::getSessionId() const
    {
        return this->sessionId;
    }

    bool Session::exists(std::string const &key) const
    {
        this->variablesMutex.lock();
        bool exists = this->variables.count(key);
        this->variablesMutex.unlock();
        return exists;
    }

}
