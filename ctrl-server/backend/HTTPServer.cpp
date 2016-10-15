#include "HTTPServer.h"

#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <unordered_map>

#include <boost/asio.hpp>

#include "String.h"
#include "IO.h"
#include "HTTPRequest.h"

namespace asio = boost::asio;
using asio::ip::tcp;

namespace vmc
{
    HTTPServer::HTTPServer(std::string const &host, int port)
    {
        std::cout << "Initializing HTTP server at " << host << ":" << port << std::endl;
        this->host = host;
        this->port = port;

        this->sessionManager = std::shared_ptr<SessionManager>(new SessionManager());
    }

    void HTTPServer::listen(std::function<void(HTTPRequest&)> callback)
    {
        asio::io_service ioService;
        auto address = asio::ip::address::from_string(this->host);
        tcp::acceptor acceptor(ioService, tcp::endpoint(address, port));

        while (true)
        {
            std::cout << "Listening..." << std::endl;
            tcp::iostream *stream = new tcp::iostream();
            acceptor.accept(*stream->rdbuf());
            std::cout << "Accepted a new connection..." << std::endl;

            auto sessionManager = this->sessionManager;

            std::thread requestThread([sessionManager, callback, stream] {
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
                    if (reqMethodField.find("GET") != std::string::npos) methodType = method::GET;
                    else if (reqMethodField.find("POST") != std::string::npos) methodType = method::POST;

                    HTTPRequest request(methodType, resource, headers, stream, sessionManager);

                    callback(request);
                }
                else
                {
                    std::cout << "Malformed HTTP request." << std::endl;
                }

                delete stream;
            });
            requestThread.detach();
        }
    }
}
