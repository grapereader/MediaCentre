#include "Application.h"

#include <vmc-libhttp/Database.h>
#include <vmc-libhttp/HTTPServer.h>
#include <vmc-libhttp/HTTPUtils.h>
#include <vmc-libhttp/Router.h>
#include <vmc-libhttp/String.h>

#include "AuthRoutes.h"
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

            routes::auth::route(*router, config);

            router->route({vmc::method::GET}, "/",
                [](RouterRequest &request) { vmc::util::redirect(request.getRequest(), "/client/index.html"); });

            router->route({vmc::method::GET}, "/config",
                [config](RouterRequest &request) {
                    json appConfig = config->get().at("app");

                    util::sendJSON(request.getRequest(), appConfig);
                });

            router->start();
        }
    }
}
