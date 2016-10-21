#include <syslog.h>

#include "Application.h"

#include "Database.h"
#include "HTTPServer.h"
#include "Router.h"

namespace vmc
{
    void start(Config const *config)
    {
        auto dbConf = config->get().at("database");
        database::initDatabase(dbConf.at("host"), dbConf.at("port"), dbConf.at("user"), dbConf.at("pass"),
            dbConf.at("database"), true, true);

        auto server = std::unique_ptr<vmc::HTTPServer>(
            new vmc::HTTPServer(config->get().at("http").at("host"), config->get().at("http").at("port")));
        auto router = std::unique_ptr<vmc::Router>(new vmc::Router(server.get()));
        router->routeStaticFolder("/client", "../frontend");

        router->route({vmc::method::GET}, "/test",
            [](vmc::HTTPRequest &request, std::vector<std::string> const &urlParts,
                          std::unordered_map<std::string, std::string> const &urlParams) {
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

        syslog(LOG_NOTICE, "Starting the router...");
        router->start();
        syslog(LOG_NOTICE, "Quitting.");
    }
}
