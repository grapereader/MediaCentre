#include "HTTPHeaders.h"

#include "String.h"

namespace vmc
{
    HTTPHeaders::HTTPHeaders()
    { }

    void HTTPHeaders::put(std::string const &key, std::string const &header)
    {
        this->map[string::toUpper(key)] = header;
    }

    void HTTPHeaders::put(std::string const &key, long header)
    {
        this->map[string::toUpper(key)] = std::to_string(header);
    }

    bool HTTPHeaders::exists(std::string const &key) const
    {
        return this->map.count(string::toUpper(key));
    }

    std::string const &HTTPHeaders::get(std::string const &key) const
    {
        return this->map.at(string::toUpper(key));
    }

    void HTTPHeaders::remove(std::string const &key)
    {
        this->map.erase(string::toUpper(key));
    }

    std::unordered_map<std::string, std::string>::const_iterator HTTPHeaders::begin() const
    {
        return this->map.begin();
    }

    std::unordered_map<std::string, std::string>::const_iterator HTTPHeaders::end() const
    {
        return this->map.end();
    }
}
