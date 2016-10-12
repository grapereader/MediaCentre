#include "HTTPRequest.h"

namespace vmc
{
    HTTPRequest::HTTPRequest(method::HTTPMethod method, std::string const &resource, std::shared_ptr<HTTPHeaders> headers, tcp::iostream *stream)
    {
        this->method = method;
        this->resource = resource;
        this->headers = headers;
        this->stream = stream;
    }

    method::HTTPMethod HTTPRequest::getMethod() const
    {
        return this->method;
    }

    std::string const *HTTPRequest::getResource() const
    {
        return &this->resource;
    }

    HTTPHeaders const *HTTPRequest::getHeaders() const
    {
        return this->headers.get();
    }

    tcp::iostream *HTTPRequest::getStream()
    {
        return this->stream;
    }

}
