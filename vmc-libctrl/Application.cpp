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
#include "Application.h"

#include <vmc-libhttp/Database.h>
#include <vmc-libhttp/HTTPServer.h>
#include <vmc-libhttp/HTTPUtils.h>
#include <vmc-libhttp/Router.h>
#include <vmc-libhttp/String.h>

#include <vmc-libstream/OmxBackend.h>

#include "AuthRoutes.h"
#include "InputRoutes.h"
#include "PlayRoutes.h"
#include "DatabaseInit.h"

namespace vmc
{
    namespace ctrl
    {
        void start(Config const *config, input::InputManager *inputManager, stream::PlaylistManager *playlistManager)
        {
            auto dbConf = config->get().at("database");
            database::initDatabase(dbConf.at("host"), dbConf.at("port"), dbConf.at("user"), dbConf.at("pass"),
                dbConf.at("database"), true);
            database::initTables();

            auto server = std::unique_ptr<vmc::HTTPServer>(
                new vmc::HTTPServer(config->get().at("http").at("host"), config->get().at("http").at("port")));
            auto router = std::unique_ptr<vmc::Router>(new vmc::Router(server.get()));

            auto frontendFolder = config->get().at("frontend").at("folder");
            std::cout << "Using static frontend asset folder " << frontendFolder << std::endl;
            router->routeStaticFolder("/client", frontendFolder);

            std::vector<RouteGroup*> routes = {
                new routes::AuthRoutes(config),
                new routes::InputRoutes(config, inputManager),
                new routes::PlayRoutes(config, playlistManager)
            };

            for (auto it = routes.begin(); it != routes.end(); it++)
            {
                (*it)->initRoutes(*router);
            }

            router->route({vmc::method::GET}, "/",
                [](RouterRequest &request) {
                    if (request.getUrlParts().size() > 1 || request.getUrlParts()[0].length() > 0)
                    {
                        QUIT_MSG(request.getRequest(), 404, "File not found");
                    }
                    vmc::util::redirect(request.getRequest(), "/client/index.html");
                });

            router->route({vmc::method::GET}, "/config",
                [config](RouterRequest &request) {
                    json appConfig = config->get().at("app");

                    util::sendJSON(request.getRequest(), appConfig);
                });

            router->start();
        }
    }
}
