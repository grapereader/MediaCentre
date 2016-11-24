#include "AuthRoutes.h"

#include "vmc-libserver/Database.h"
#include "vmc-libserver/HTTPUtils.h"

using json = nlohmann::json;

namespace vmc
{
    namespace routes
    {
        namespace auth
        {
            void route(Router &router)
            {
                router.route({vmc::method::GET}, "/loginStatus",
                    [](auto request, auto urlParts, auto urlParams) {
                        std::shared_ptr<Session> session = request.initSession();

                        json response = {{"loggedIn", false}};

                        if (session->exists("authenticated") && session->get<bool>("authenticated"))
                        {
                            response["loggedIn"] = true;
                            response["user"] = session->get<std::string>("username");
                            if (session->exists("email"))
                            {
                                response["email"] = session->get<std::string>("email");
                            }
                        }

                        util::sendJSON(request, response);
                    });

                router.route({vmc::method::POST}, "/login",
                    [](auto request, auto urlParts, auto urlParams) {
                        if (urlParams.count("user") == 0)
                            QUIT_MSG(request, 400, "{ \"okay\": false, \"error\": \"Bad request\" }");

                        json response = {};
                        std::string user = urlParams.at("user");
                        if (user == "guest")
                        {
                            std::shared_ptr<Session> session = request.initSession();
                            session->put("authenticated", true);
                            session->put("access-level", 1);
                            session->put<std::string>("username", "Guest");
                            response["okay"] = true;
                            response["user"] = {{"name", "Guest"}};
                        }
                        else
                        {
                            auto db = database::getDatabase();
                            auto query = db->store("SELECT * FROM users WHERE username = %0q", {user});

                            if (!query || query.num_rows() == 0)
                            {
                                QUIT_MSG(request, 406, "{\"okay\": false, \"error\": \"Invalid login\"}");
                            }

                            auto userData = query[0];

                            response["okay"] = true;
                            response["user"] = {
                                {"name", userData["username"].data()}, {"email", userData["email"].data()}};
                        }

                        util::sendJSON(request, response);
                    });

                router.route({vmc::method::POST}, "/logout",
                    [](HTTPRequest &request, auto urlParts, auto urlParams) {
                        auto session = request.initSession();
                        session->put("authenticated", false);
                        session->put("access-level", 0);
                        session->put<std::string>("username", "");
                        json response = {};
                        response["okay"] = true;
                        response["msg"] = "Logged out successfully";
                        util::sendJSON(request, response);
                    });
            }
        }
    }
}
