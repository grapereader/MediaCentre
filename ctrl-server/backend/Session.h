#ifndef SESSION_H
#define SESSION_H

#include <boost/variant.hpp>
#include <ctime>
#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>

namespace vmc
{
    typedef std::shared_ptr<void> VoidPtr;
    typedef boost::variant<std::string, int, double, bool, VoidPtr> SessionVar;

    class Session
    {
    public:
        Session(std::string const &sessionId);
        std::string const &getSessionId() const;
        std::time_t getAge() const;

        bool exists(std::string const &key) const;

        template <typename T>
        T get(std::string const &key)
        {
            this->variablesMutex.lock();
            T val = boost::get<T>(this->variables[key]);
            this->variablesMutex.unlock();
            return val;
        }

        template <typename T>
        void put(std::string const &key, T const &val)
        {
            this->variablesMutex.lock();
            this->variables[key] = val;
            this->variablesMutex.unlock();
        }

    private:
        std::string sessionId;
        std::time_t createdTime;

        std::unordered_map<std::string, SessionVar> variables;
        mutable std::mutex variablesMutex;
    };
}

#endif
