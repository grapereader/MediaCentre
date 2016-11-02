#include "Application.h"
#include "Database.h"
#include "HTTPServer.h"
#include "HTTPUtils.h"
#include "Router.h"

namespace vmc
{
    void start(Config const *config)
    {
        auto dbConf = config->get().at("database");
        database::initDatabase(dbConf.at("host"), dbConf.at("port"), dbConf.at("user"), dbConf.at("pass"),
            dbConf.at("database"), true);

        auto server = std::unique_ptr<vmc::HTTPServer>(
            new vmc::HTTPServer(config->get().at("http").at("host"), config->get().at("http").at("port")));
        auto router = std::unique_ptr<vmc::Router>(new vmc::Router(server.get()));

        auto frontendFolder = config->get().at("frontend").at("folder");
        std::cout << "Using static frontend asset folder " << frontendFolder << std::endl;
        router->routeStaticFolder("/client", frontendFolder);

        router->route({vmc::method::GET}, "/",
            [](auto request, auto urlParts, auto urlParams) { vmc::util::redirect(request, "/client/index.html"); });

        router->route({vmc::method::GET}, "/initDatabase",
            [](auto request, auto urlParts, auto urlParams) {
                request.getResponseHeaders()->put("Content-Type", "text/plain");
                request.sendResponseHeaders(200);
                auto *stream = &request.getStream();
                *stream << "Initializing database...\r\n";
                try
                {
                    auto db = database::getDatabase();
                    *stream << "Got database\r\n";
                }
                catch (std::exception e)
                {
                    *stream << "Error while getting database connection\r\n";
                }
            });

        router->route({vmc::method::GET}, "/test",
            [](auto request, auto urlParts, auto urlParams) {
                auto session = request.initSession();
                std::string greeting = "Meh. Strangers are lame...";
                if (session->exists("greeting"))
                {
                    greeting = session->template get<std::string>("greeting");
                }
                std::string resp = "Hello there... <p>";
                resp.append(greeting);

                session->template put<std::string>("greeting", "Hey, you've been here before!");

                request.getResponseHeaders()->put("Content-Length", resp.length());
                request.sendResponseHeaders(200);

                request.getStream() << resp << "\r\n";
            });

        router->start();
    }
}
