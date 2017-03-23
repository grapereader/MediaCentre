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
#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <memory>
#include <boost/asio.hpp>
#include "HTTPHeaders.h"
#include "SessionManager.h"
#include "PostData.h"

using boost::asio::ip::tcp;

namespace vmc
{

    namespace method
    {
        enum HTTPMethod
        {
            INVALID, GET, POST
        };
    }

    class HTTPRequest
    {
    public:
        HTTPRequest(method::HTTPMethod method, std::string const &resource, std::shared_ptr<HTTPHeaders> headers, tcp::iostream *stream);
        method::HTTPMethod getMethod() const;
        std::string const &getResource() const;
        HTTPHeaders const &getHeaders() const;
        std::shared_ptr<HTTPHeaders> getResponseHeaders();
        void sendResponseHeaders(int code);
        tcp::iostream &getStream();
    private:
        method::HTTPMethod method;
        std::string resource;
        std::shared_ptr<HTTPHeaders> headers;
        std::shared_ptr<HTTPHeaders> responseHeaders;
        tcp::iostream *stream;
    };
}

#endif
