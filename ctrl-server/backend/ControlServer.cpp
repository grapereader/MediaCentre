#include <iostream>
#include <memory>

#include "HTTPServer.h"
#include "Router.h"

#define VERSION "0.0.1"

int main(int argc, char **argv)
{
    std::cout << "Running ViaWare Control Server v" << VERSION << std::endl;

    auto server = std::unique_ptr<vmc::HTTPServer>(new vmc::HTTPServer("0.0.0.0", 8080));
    auto router = std::unique_ptr<vmc::Router>(new vmc::Router(server.get()));
    
    router->routeStaticFolder("/client", "../frontend");

    router->start();

    return 0;
}
