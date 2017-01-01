#include "Application.h"

#include <vmc-libhttp/Database.h>
#include <vmc-libhttp/HTTPServer.h>
#include <vmc-libhttp/HTTPUtils.h>
#include <vmc-libhttp/Router.h>
#include <vmc-libhttp/String.h>

#include "AuthRoutes.h"
#include "InputRoutes.h"
#include "DatabaseInit.h"

namespace vmc
{
    namespace ctrl
    {
        void start(Config const *config)
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
                new routes::InputRoutes(config)
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
