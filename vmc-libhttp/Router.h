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
