#include "Router.h"

#include <iostream>

#include "IO.h"
#include "String.h"

namespace vmc
{
    Router::Router(HTTPServer *server)
    {
        this->server = server;
        this->sessionManager = std::shared_ptr<SessionManager>(new SessionManager());
    }

    void Router::start()
    {
        this->server->listen([this](HTTPRequest &request) { this->handleRequest(request); });
    }

    void Router::handleRequest(HTTPRequest &request)
    {
        std::string resourceUpper = string::toUpper(request.getResource());
        if (this->fileRoutes.count(resourceUpper))
        {
            std::string filePath = this->fileRoutes[resourceUpper];
            if (io::fileExists(filePath))
            {
                std::cout << "Router: Routing \"" << resourceUpper << "\" to static file \"" << filePath << "\""
                          << std::endl;
                auto size = io::getFileSize(filePath);
                request.getResponseHeaders()->put("Content-Length", size);
                request.sendResponseHeaders(200);
                io::writeFileToStream(filePath, request.getStream());
                return;
            }
        }

        std::vector<std::string> urlParts = string::split(request.getResource(), "/");

        unsigned int max = 0;
        std::string route, folder;
        for (auto it = this->folderRoutes.begin(); it != this->folderRoutes.end(); it++)
        {
            std::string currRoute = it->first;
            if (string::startsWith(resourceUpper, currRoute))
            {
                if (currRoute.length() > max)
                {
                    max = currRoute.length();
                    route = currRoute;
                    folder = it->second;
                }
            }
        }

        if (max > 0)
        {
            std::string relative =
                request.getResource().substr(route.length(), request.getResource().length() - route.length());
            if (string::startsWith(relative, "/")) relative = relative.substr(1, relative.length() - 1);

            if (string::startsWith(relative, "../") || string::contains(relative, "/../"))
            {
                request.sendResponseHeaders(403);
                request.getStream() << "403 Forbidden -> Relative directory access not allowed\r\n";
                return;
            }

            std::string file(folder);
            file.append("/");
            file.append(relative);

            if (io::fileExists(file))
            {
                std::cout << "Router: Routing \"" << resourceUpper << "\" to file in static folder \"" << file << "\""
                          << std::endl;
                request.getResponseHeaders()->put("Content-Length", io::getFileSize(file));
                request.sendResponseHeaders(200);
                io::writeFileToStream(file, request.getStream());
                return;
            }
        }

        max = 0;
        route = "";
        RouterCallback callback;
        for (auto it = this->routes.begin(); it != this->routes.end(); it++)
        {
            std::string currRoute = it->first;
            if (string::startsWith(resourceUpper, currRoute))
            {
                auto routeData = it->second;
                auto methods = routeData.first;
                bool compatible = false;

                for (unsigned int i = 0; i < methods.size(); i++)
                {
                    if (methods[i] == request.getMethod())
                    {
                        compatible = true;
                        break;
                    }
                }

                if (compatible && currRoute.length() > max)
                {
                    max = currRoute.length();
                    route = currRoute;
                    callback = routeData.second;
                }
            }
        }

        if (max > 0)
        {
            std::string paramString =
                request.getResource().substr(route.length(), request.getResource().length() - route.length());
            auto urlParts = string::split(paramString, "?", 1);
            std::unordered_map<std::string, std::string> urlParams;
            if (urlParts.size() > 1)
            {
                std::string queryString = urlParts[1];
                auto queryParts = string::split(queryString, "&");
                for (unsigned int i = 0; i < queryParts.size(); i++)
                {
                    std::string param = queryParts[i];
                    std::vector<std::string> keyVal = string::split(param, "=", 1);
                    if (keyVal.size() >= 2)
                    {
                        urlParams[keyVal[0]] = keyVal[1];
                    }
                }
            }

            auto postData = std::unique_ptr<PostData>(new PostData());
            bool hasPostData = false;

            if (request.getMethod() == method::POST && request.getHeaders().exists("Content-Type"))
            {
                std::string type = request.getHeaders().get("Content-Type");
                bool urlEncoded = string::contains(type, "form-urlencoded");
                if (urlEncoded)
                {
                    if (!request.getHeaders().exists("Content-Length"))
                    {
                        request.sendResponseHeaders(411);
                        return;
                    }

                    std::unordered_map<std::string, std::string> postUrlParams;

                    int length = std::stoi(request.getHeaders().get("Content-Length"));
                    std::string body(length, 0);
                    request.getStream().read(&body[0], length);
                    auto postParts = string::split(body, "&");
                    for (auto it = postParts.begin(); it != postParts.end(); it++)
                    {
                        auto postParam = string::split(*it, "=");
                        if (postParam.size() >= 2)
                        {
                            postUrlParams[postParam[0]] = postParam[1];
                        }
                    }

                    hasPostData = true;
                    postData->setUrl(postUrlParams);
                }

                bool jsonData = string::contains(type, "json");
                if (jsonData)
                {
                    if (!request.getHeaders().exists("Content-Length"))
                    {
                        request.sendResponseHeaders(411);
                        return;
                    }

                    int length = std::stoi(request.getHeaders().get("Content-Length"));
                    std::string body(length, 0);
                    request.getStream().read(&body[0], length);
                    json jsonParams = json::parse(body);
                    hasPostData = true;
                    postData->setJson(jsonParams);
                }
            }

            std::string pathString = urlParts[0];
            if (string::startsWith(pathString, "/")) pathString = pathString.substr(1, pathString.length() - 1);

            auto pathParts = string::split(pathString, "/");
            RouterRequest routerRequest(&request, &pathParts, &urlParams, this->sessionManager);

            if (hasPostData) routerRequest.setPostData(std::move(postData));

            std::cout << "Routing \"" << resourceUpper << "\" to \"" << route << "\"..." << std::endl;
            callback(routerRequest);
            return;
        }

        std::cout << "Router: Could not find a route for \"" << request.getResource() << "\"" << std::endl;
        request.sendResponseHeaders(404);
        request.getStream() << "<h1>Error - 404</h1><hr>\r\n";
        request.getStream() << "Could not find the requested resource \"" << request.getResource() << "\"...\r\n";
    }

    void Router::route(
        std::vector<method::HTTPMethod> const &methods, std::string const &path, RouterCallback const &callback)
    {
        this->routes[string::toUpper(path)] =
            std::pair<std::vector<method::HTTPMethod>, RouterCallback>(methods, callback);
    }

    void Router::routeStaticFolder(std::string const &path, std::string const &folder)
    {
        this->folderRoutes[string::toUpper(path)] = folder;
    }

    void Router::routeStaticFile(std::string const &path, std::string const &file)
    {
        this->fileRoutes[string::toUpper(path)] = file;
    }
}
