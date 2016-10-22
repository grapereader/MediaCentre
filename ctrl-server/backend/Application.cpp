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
        router->routeStaticFolder("/client", "../frontend");

        router->route({vmc::method::GET}, "/",
            [](auto request, auto urlParts, auto urlParams) { vmc::util::redirect(request, "/client/index.html"); });

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
