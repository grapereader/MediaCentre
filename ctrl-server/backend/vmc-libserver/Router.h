#ifndef ROUTER_H
#define ROUTER_H

#include <functional>

#include "HTTPServer.h"

namespace vmc
{
    typedef std::function<void(
        HTTPRequest &, std::vector<std::string> const &, std::unordered_map<std::string, std::string> const &)>
        RouterCallback;

    class Router
    {
    public:
        Router(HTTPServer *server);
        void route(
            std::vector<method::HTTPMethod> const &methods, std::string const &path, RouterCallback const &callback);
        void routeStaticFolder(std::string const &path, std::string const &folder);
        void routeStaticFile(std::string const &path, std::string const &file);

        void start();

    private:
        HTTPServer *server;

        std::unordered_map<std::string, std::pair<std::vector<method::HTTPMethod>, RouterCallback>> routes;
        std::unordered_map<std::string, std::string> folderRoutes;
        std::unordered_map<std::string, std::string> fileRoutes;

        void handleRequest(HTTPRequest &request);
    };
}

#endif
