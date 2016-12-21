#include "AuthRoutes.h"

#include "vmc-libserver/Auth.h"
#include "vmc-libserver/Database.h"
#include "vmc-libserver/HTTPUtils.h"

#include "vmc-libserver/String.h"

#include "AppUtils.h"

using json = nlohmann::json;

namespace vmc
{
    namespace routes
    {
        namespace auth
        {
            namespace glob
            {
                Config const *config;
            }

            void loginStatus(RouterRequest &request)
            {
                std::shared_ptr<Session> session = request.initSession();

                json response = {{"loggedIn", false}};

                if (session->exists("authenticated") && session->get<bool>("authenticated"))
                {
                    response["loggedIn"] = true;
                    response["username"] = session->get<std::string>("username");
                    if (session->exists("email"))
                    {
                        response["email"] = session->get<std::string>("email");
                    }
                }

                util::sendJSON(request.getRequest(), response);
            }

            void login(RouterRequest &request)
            {
                if (!request.getPostData().hasJsonData()) QUIT_BAD_REQUEST(request.getRequest());

                json requestJson = request.getPostData().getJson();
                if (requestJson.count("username") == 0) QUIT_BAD_REQUEST(request.getRequest());

                json response = {};
                std::string user = requestJson["username"];
                std::shared_ptr<Session> session = request.initSession();
                if (user == "guest")
                {
                    if ((bool) glob::config->get()["app"]["guest"] != true) QUIT_MSG(request.getRequest(), 403, "Guest access disabled");

                    std::string displayName = "Guest";
                    if (requestJson.count("displayName") > 0)
                    {
                        displayName = requestJson["displayName"];
                    }
                    session->put("authenticated", true);
                    session->put("access-level", 1);
                    session->put("username", displayName);
                    response["okay"] = true;
                    response["user"] = {{"username", displayName}, {"privilege", 1}};
                }
                else
                {
                    if (requestJson.count("password") == 0) QUIT_BAD_REQUEST(request.getRequest());

                    auto db = database::getDatabase();
                    auto query = db->store("SELECT * FROM users WHERE username = %0q", {user});

                    if (!query || query.num_rows() == 0)
                    {
                        QUIT_MSG(request.getRequest(), 406, "{\"okay\": false, \"error\": \"Invalid login\"}");
                    }

                    auto userData = query[0];

                    auto hash = (const char *) userData["password"];
                    std::string password = requestJson["password"];
                    auto validPassword = vmc::auth::comparePassword(hash, password);

                    response["okay"] = validPassword;

                    if (validPassword)
                    {
                        response["user"] = {{"username", (const char *) userData["username"]},
                            {"email", (const char *) userData["email"]}, {"privilege", (int) userData["privilege"]}};

                        session->put("authenticated", true);
                        session->put("access-level", (int) userData["privilege"]);
                        session->put<std::string>("username", (const char *) userData["username"]);
                        session->put<std::string>("email", (const char *) userData["email"]);
                    }
                }

                util::sendJSON(request.getRequest(), response);
            }

            void logout(RouterRequest &request)
            {
                auto session = request.initSession();
                session->put("authenticated", false);
                session->put("access-level", 0);
                session->put<std::string>("username", "");
                json response = {};
                response["okay"] = true;
                response["msg"] = "Logged out successfully";
                util::sendJSON(request.getRequest(), response);
            }

            bool validateUsername(std::string username)
            {
                return username.length() >= 4 && string::isAlphaNumeric(username);
            }

            bool validatePassword(std::string password)
            {
                return password.length() >= 8;
            }

            bool validateEmail(std::string email)
            {
                std::cout << email << std::endl;
                if (!string::contains(email, "@")) return false;
                auto emailParts = string::split(email, "@");

                if (emailParts.size() != 2) return false;
                if (emailParts[0].length() == 0 || emailParts[1].length() <= 4) return false;
                return true;
            }

            void registr(RouterRequest &request)
            {
                if ((bool) glob::config->get().at("app").at("registration") != true) QUIT_MSG(request.getRequest(), 403, "Registration disabled");
                if (!request.getPostData().hasJsonData()) QUIT_BAD_REQUEST(request.getRequest());

                auto reqJson = request.getPostData().getJson();
                if (!utils::jsonHasKeys(reqJson, { "username", "password", "email" })) QUIT_BAD_REQUEST(request.getRequest());

                std::string username = reqJson["username"];
                std::string password = reqJson["password"];
                std::string email = reqJson["email"];

                bool usernameValid = validateUsername(username);
                bool passwordValid = validatePassword(password);
                bool emailValid = validateEmail(email);

                if (!(usernameValid && passwordValid && emailValid))
                {
                    json errJson = {
                        {"okay", false},
                        {"msg", "Invalid user details"},
                        {"valid", {
                            {"username", usernameValid},
                            {"password", passwordValid},
                            {"email", emailValid}
                        }}
                    };

                    QUIT_JSON(request.getRequest(), 406, errJson);
                }

                auto db = database::getDatabase();
                auto result = db->store("SELECT COUNT(*) AS count FROM users WHERE username = %0q OR email = %1q", { username, email });

                if (result.num_rows() > 0 && (int) result[0]["count"] > 0)
                {
                    json errJson = {
                        {"okay", false},
                        {"msg", "User already exists with provided username/email"}
                    };

                    QUIT_JSON(request.getRequest(), 406, errJson);
                }

                std::string passHash = vmc::auth::createHash(password);

                db->execute("INSERT INTO users (username, password, email, privilege) VALUES (%0q, %1q, %2q, %3q)", { username, passHash, email, 2 });

                json respJson = {
                    {"okay", true},
                    {"msg", "User created successfully, you may now login"}
                };
                util::sendJSON(request.getRequest(), respJson);
            }

            void route(Router &router, Config const *config)
            {
                glob::config = config;
                router.route({vmc::method::GET}, "/loginStatus", loginStatus);
                router.route({vmc::method::POST}, "/login", login);
                router.route({vmc::method::POST}, "/logout", logout);
                router.route({vmc::method::POST}, "/register", registr);
            }
        }
    }
}
