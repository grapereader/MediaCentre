/*
 * Copyright 2017 Seth Traverse
 *
 * This file is part of ViaWare Media Centre.
 *
 * ViaWare Media Centre is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ViaWare Media Centre is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * with ViaWare Media Centre.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "HTTPRequest.h"

#include "HTTPUtils.h"

namespace vmc
{
    HTTPRequest::HTTPRequest(method::HTTPMethod method, std::string const &resource, std::shared_ptr<HTTPHeaders> headers, tcp::iostream *stream)
    {
        this->method = method;
        this->resource = resource;
        this->headers = headers;
        this->stream = stream;
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
