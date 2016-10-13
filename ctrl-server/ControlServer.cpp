#include <iostream>
#include <memory>

#include "HTTPServer.h"
#include "Router.h"

#define VERSION "0.0.1"

void handleRequest(vmc::HTTPRequest &request)
{
    if (request.getMethod() == vmc::method::INVALID)
    {
        std::cout << "Not handling invalid HTTP request" << std::endl;
    }
    std::cout << "Handling " << (request.getMethod() == vmc::method::GET ? "GET" : "POST") << " request for " << request.getResource() << std::endl;

    vmc::HTTPHeaders responseHeaders;
    responseHeaders.put("Content-Type", "text/html");
    
    request.sendResponseHeaders(200, responseHeaders);

    request.getStream() << "This is HTML?\r\n";
}

int main(int argc, char **argv)
{
    std::cout << "Running ViaWare Control Server v" << VERSION << std::endl;

    auto server = std::unique_ptr<vmc::HTTPServer>(new vmc::HTTPServer("0.0.0.0", 8080));
    auto router = std::unique_ptr<vmc::Router>(new vmc::Router(server.get()));
    
    router->routeStaticFile("/test", "./HTTPServer.cpp");
    router->routeStaticFolder("/test2", "../");

    router->start();

    return 0;
}
