/*
 * Copyright 2017 Seth Traverse
 *
 * This file is part of ViaWare Media Centre.
 *
 * ViaWare Media Centre is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ViaWare Media Centre is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * with ViaWare Media Centre.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef ROUTERREQUEST_H
#define ROUTERREQUEST_H

#include "HTTPRequest.h"
#include "PostData.h"

namespace vmc
{
    class RouterRequest
    {
    public:
        RouterRequest(HTTPRequest *request, std::vector<std::string> const *urlParts, std::unordered_map<std::string, std::string> const *urlParams, std::shared_ptr<SessionManager> sessionManager);
        std::shared_ptr<Session> initSession();

        void setPostData(std::unique_ptr<PostData> postData);

        HTTPRequest &getRequest();
        std::vector<std::string> const &getUrlParts() const;
        std::unordered_map<std::string, std::string> const &getUrlParams() const;
        PostData const &getPostData() const;
    private:
        HTTPRequest *request;
        std::vector<std::string> const *urlParts;
        std::unordered_map<std::string, std::string> const *urlParams;
        std::unique_ptr<PostData> postData;
        std::shared_ptr<SessionManager> sessionManager;
    };
}

#endif
