#include "HTTPRequest.h"

#include "HTTPUtils.h"

namespace vmc
{
    HTTPRequest::HTTPRequest(method::HTTPMethod method, std::string const &resource, std::shared_ptr<HTTPHeaders> headers, tcp::iostream *stream, std::shared_ptr<SessionManager> sessionManager)
    {
        this->method = method;
        this->resource = resource;
        this->headers = headers;
        this->stream = stream;
        this->sessionManager = sessionManager;
        this->responseHeaders = std::shared_ptr<HTTPHeaders>(new HTTPHeaders());
    }

    method::HTTPMethod HTTPRequest::getMethod() const
    {
        return this->method;
    }

    std::string const &HTTPRequest::getResource() const
    {
        return this->resource;
    }

    HTTPHeaders const &HTTPRequest::getHeaders() const
    {
        return *this->headers.get();
    }

    std::shared_ptr<HTTPHeaders> HTTPRequest::getResponseHeaders()
    {
        return this->responseHeaders;
    }

    tcp::iostream &HTTPRequest::getStream()
    {
        return *this->stream;
    }

    std::shared_ptr<Session> HTTPRequest::initSession()
    {
        return session::init(*this->sessionManager, *this->headers, *this->responseHeaders);
    }

    void HTTPRequest::sendResponseHeaders(int code)
    {
        char const *status = util::getStatus(code);
        *this->stream << "HTTP/1.1 " << code << " " << status << "\r\n";

        for (auto it = this->responseHeaders->begin(); it != this->responseHeaders->end(); it++)
        {
            *this->stream << it->first << ": " << it->second << "\r\n";
        }
        *this->stream << "\r\n";
    }
}
