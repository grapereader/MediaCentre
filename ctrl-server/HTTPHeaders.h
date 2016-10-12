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
        std::string const *get(std::string const &key) const;
        void remove(std::string const &key);
    private:
        std::unordered_map<std::string, std::string> map;
    };
}

#endif
