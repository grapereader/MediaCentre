#ifndef HTTPHEADERS_H
#define HTTPHEADERS_H

#include <unordered_map>
#include <string>

namespace vmc
{
    class HTTPHeaders
    {
    public:
        HTTPHeaders();
        void put(std::string const &key, std::string const &header);
        void put(std::string const &key, long header);
        std::string const *get(std::string const &key) const;
        void remove(std::string const &key);
        std::unordered_map<std::string, std::string>::const_iterator begin() const;
        std::unordered_map<std::string, std::string>::const_iterator end() const;
    private:
        std::unordered_map<std::string, std::string> map;
    };
}

#endif
