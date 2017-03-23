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
#include "HTTPServer.h"

#include <iostream>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

#include <boost/asio.hpp>

#include "HTTPRequest.h"
#include "HTTPUtils.h"
#include "IO.h"
#include "String.h"

namespace asio = boost::asio;
using asio::ip::tcp;

namespace vmc
{
    HTTPServer::HTTPServer(std::string const &host, int port)
    {
        std::cout << "Initializing HTTP server at " << host << ":" << port << std::endl;
        this->host = host;
        this->port = port;

    }

    void HTTPServer::listen(std::function<void(HTTPRequest &)> callback)
    {
        asio::io_service ioService;
        auto address = asio::ip::address::from_string(this->host);
        tcp::acceptor acceptor(ioService, tcp::endpoint(address, port));

        while (true)
        {
            tcp::iostream *stream = new tcp::iostream();
            acceptor.accept(*stream->rdbuf());

            std::thread requestThread([callback, stream] {
                std::string line;

                io::getLineNoReturn(*stream, line);

                auto parts = string::split(line, " ");

                if (parts.size() == 3)
                {
                    std::string method = parts[0];
                    std::string resource = parts[1];
                    std::string version = parts[2];

                    auto headers = std::shared_ptr<HTTPHeaders>(new HTTPHeaders());

                    io::getLineNoReturn(*stream, line);
                    while (line.length() > 0)
                    {
                        auto headerParts = string::split(line, ":", 1);

                        if (headerParts.size() >= 2)
                        {
                            std::string key = string::trim(headerParts[0]);
                            std::string val = string::trim(headerParts[1]);

                            headers->put(key, val);
                        }
                        else
                        {
                            std::cout << "Malformed request header \"" << line << "\"" << std::endl;
                        }

                        io::getLineNoReturn(*stream, line);
                    }

                    method::HTTPMethod methodType = method::INVALID;
                    std::string reqMethodField = string::toUpper(method);
                    if (reqMethodField.find("GET") != std::string::npos)
                        methodType = method::GET;
                    else if (reqMethodField.find("POST") != std::string::npos)
                        methodType = method::POST;

                    HTTPRequest request(methodType, resource, headers, stream);

                    try
                    {
                        callback(request);
                    }
                    catch (std::exception e)
                    {
                        *stream << "HTTP 500 " << util::getStatus(500) << "\r\n\r\n";
                        *stream << "An exception was thrown while processing your request\r\n";
                    }
                }
                else
                {
                    std::cout << "Malformed HTTP request." << std::endl;
                    *stream << "HTTP 400 " << util::getStatus(400) << "\r\n\r\n";
                    *stream << "Malformed HTTP request\r\n";
                }

                delete stream;
            });
            requestThread.detach();
        }
    }
}
