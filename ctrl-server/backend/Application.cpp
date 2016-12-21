#include "Application.h"
#include "vmc-libserver/Database.h"
#include "vmc-libserver/HTTPServer.h"
#include "vmc-libserver/HTTPUtils.h"
#include "vmc-libserver/Router.h"
#include "vmc-libserver/String.h"

#include "DatabaseInit.h"
#include "AuthRoutes.h"

namespace vmc
{
    void start(Config const *config)
    {
        auto dbConf = config->get().at("database");
        database::initDatabase(
            dbConf.at("host"), dbConf.at("port"), dbConf.at("user"), dbConf.at("pass"), dbConf.at("database"), true);
        database::initTables();

        auto server = std::unique_ptr<vmc::HTTPServer>(
            new vmc::HTTPServer(config->get().at("http").at("host"), config->get().at("http").at("port")));
        auto router = std::unique_ptr<vmc::Router>(new vmc::Router(server.get()));

        auto frontendFolder = config->get().at("frontend").at("folder");
        std::cout << "Using static frontend asset folder " << frontendFolder << std::endl;
        router->routeStaticFolder("/client", frontendFolder);

        routes::auth::route(*router);

        router->route({vmc::method::GET}, "/",
            [](RouterRequest &request) {
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
