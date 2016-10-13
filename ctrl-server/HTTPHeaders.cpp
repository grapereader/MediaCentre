#include "HTTPHeaders.h"

namespace vmc
{
    HTTPHeaders::HTTPHeaders()
    { }

    void HTTPHeaders::put(std::string const &key, std::string const &header)
    {
        this->map[key] = header;
    }

    void HTTPHeaders::put(std::string const &key, long header)
    {
        this->map[key] = std::to_string(header);
    }

    std::string const *HTTPHeaders::get(std::string const &key) const
    {
        return &this->map.at(key);
    }

    void HTTPHeaders::remove(std::string const &key)
    {
        this->map.erase(key);
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
