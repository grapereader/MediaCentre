#include "HTTPHeaders.h"

namespace vmc
{
    HTTPHeaders::HTTPHeaders()
    { }

    void HTTPHeaders::put(std::string const &key, std::string const &header)
    {
        this->map[key] = header;
    }

    std::string const *HTTPHeaders::get(std::string const &key) const
    {
        return &this->map.at(key);
    }

    void HTTPHeaders::remove(std::string const &key)
    {
        this->map.erase(key);
    }
}
