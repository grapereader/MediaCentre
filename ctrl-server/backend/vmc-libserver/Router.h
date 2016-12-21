#ifndef ROUTER_H
#define ROUTER_H

#include <functional>

#include "HTTPServer.h"
#include "RouterRequest.h"

namespace vmc
{
    typedef std::function<void(RouterRequest &)> RouterCallback;

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
        std::shared_ptr<SessionManager> sessionManager;
    };
}

#endif
