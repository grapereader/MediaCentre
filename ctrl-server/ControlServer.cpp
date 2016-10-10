#include <iostream>
#include <memory>

#include "HTTPServer.h"


#define VERSION "0.0.1"

int main(int argc, char **argv)
{
    std::cout << "Running ViaWare Control Server v" << VERSION << std::endl;

    auto server = std::unique_ptr<vmc::HTTPServer>(new vmc::HTTPServer("0.0.0.0", 8080));
    server->listen([]() {
        std::cout << "Got connection!" << std::endl;
    });

    return 0;
}
