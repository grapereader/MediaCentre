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
#include "RouterRequest.h"

namespace vmc
{
    RouterRequest::RouterRequest(HTTPRequest *request, std::vector<std::string> const *urlParts, std::unordered_map<std::string, std::string> const *urlParams, std::shared_ptr<SessionManager> sessionManager)
    {
        this->request = request;
        this->urlParts = urlParts;
        this->urlParams = urlParams;
        this->sessionManager = sessionManager;
    }

    std::shared_ptr<Session> RouterRequest::initSession()
    {
        return session::init(*this->sessionManager, this->request->getHeaders(), *this->request->getResponseHeaders());
    }

    void RouterRequest::setPostData(std::unique_ptr<PostData> postData)
    {
        this->postData = std::move(postData);
    }

    HTTPRequest &RouterRequest::getRequest()
    {
        return *this->request;
    }

    std::vector<std::string> const &RouterRequest::getUrlParts() const
    {
        return *this->urlParts;
    }

    std::unordered_map<std::string, std::string> const &RouterRequest::getUrlParams() const
    {
        return *this->urlParams;
    }

    PostData const &RouterRequest::getPostData() const
    {
        if (this->postData) return *this->postData;
        throw std::runtime_error("This request has no post data");
    }
}
