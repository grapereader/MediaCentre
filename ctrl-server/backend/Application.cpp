#include "Application.h"
#include "Database.h"
#include "HTTPServer.h"
#include "HTTPUtils.h"
#include "Router.h"
#include "String.h"

namespace vmc
{
    void start(Config const *config)
    {
        auto dbConf = config->get().at("database");
        database::initDatabase(
            dbConf.at("host"), dbConf.at("port"), dbConf.at("user"), dbConf.at("pass"), dbConf.at("database"), true);

        auto server = std::unique_ptr<vmc::HTTPServer>(
            new vmc::HTTPServer(config->get().at("http").at("host"), config->get().at("http").at("port")));
        auto router = std::unique_ptr<vmc::Router>(new vmc::Router(server.get()));

        auto frontendFolder = config->get().at("frontend").at("folder");
        std::cout << "Using static frontend asset folder " << frontendFolder << std::endl;
        router->routeStaticFolder("/client", frontendFolder);

        router->route({vmc::method::GET}, "/",
            [](auto request, auto urlParts, auto urlParams) { vmc::util::redirect(request, "/client/index.html"); });

        router->route({vmc::method::POST}, "/login",
            [](auto request, auto urlParts, auto urlParams) {
                if (urlParams.count("user") == 0)
                    QUIT_MSG(request, 400, "{ \"okay\": false, \"error\": \"Bad request\" }");

                std::string user = urlParams.at("user");
                if (user == "guest")
                {
                    std::shared_ptr<Session> session = request.initSession();
                    session->put("authenticated", true);
                    session->put("access-level", 1);
                }
                else
                {
                    auto db = database::getDatabase();
                    auto query = db->store("SELECT * FROM users WHERE name = %0q", { user });

                    if (!query || query.num_rows() == 0)
                    {
                        QUIT_MSG(request, 406, "{\"okay\": false, \"error\": \"Invalid login\"}");
                    }

                    auto userData = query[0];

                    json response = {
                        {"okay", true},
                        {"user", {
                            {"name", userData["username"].data()},
                            {"email", userData["email"].data()}
                        }}
                    };

                    std::string jsonString = response.dump(4);

                    request.getResponseHeaders()->put("Content-Type", "application/json");
                    request.getResponseHeaders()->put("Content-Length", jsonString.length());

                    request.sendResponseHeaders(200);
                    request.getStream() << jsonString;

                }
            });

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
