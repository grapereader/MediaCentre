#include "HTTPServer.h"

#include <iostream>
#include <thread>
#include <vector>
#include <boost/asio.hpp>

#include "ThreadPool.h"

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

    void HTTPServer::listen(std::function<void(void)> callback)
    {
        asio::io_service ioService;
        auto address = asio::ip::address::from_string(this->host);
        tcp::acceptor acceptor(ioService, tcp::endpoint(address, port));

        auto pool = std::unique_ptr<ThreadPool>(new ThreadPool(4));

        while (true)
        {
            tcp::socket client(ioService);
            std::cout << "Listening..." << std::endl;
            acceptor.accept(client);
            boost::system::error_code ignored;
            boost::asio::write(client, boost::asio::buffer("Suh"), ignored);
            std::cout << "Accepted client " << client.remote_endpoint() << std::endl;
            pool->task(callback);
        }
    }
}
