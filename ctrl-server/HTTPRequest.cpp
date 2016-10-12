#include "HTTPRequest.h"

namespace vmc
{
    HTTPRequest::HTTPRequest(method::HTTPMethod method, std::shared_ptr<HTTPHeaders> headers, tcp::iostream *stream)
    {
        this->method = method;
        this->headers = headers;
        this->stream = stream;
    }

    method::HTTPMethod HTTPRequest::getMethod() const
    {
        return this->method;
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
