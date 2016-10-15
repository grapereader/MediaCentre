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

    router->route({vmc::method::GET}, "/test", [](vmc::HTTPRequest &request, std::vector<std::string> const &urlParts, std::unordered_map<std::string, std::string> const &urlParams)
    {
        auto session = request.initSession();
        std::string greeting = "Meh. Strangers are lame...";
        if (session->exists("greeting"))
        {
            greeting = session->get<std::string>("greeting");
        }
        std::string resp = "Hello there... <p>";
        resp.append(greeting);

        session->put<std::string>("greeting", "Hey, you've been here before!");

        request.getResponseHeaders()->put("Content-Length", resp.length());
        request.sendResponseHeaders(200);

        request.getStream() << resp << "\r\n";
    });

    router->start();

    return 0;
}
