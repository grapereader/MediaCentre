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
#ifndef HTTPUTILS_H
#define HTTPUTILS_H

#include <string>
#include "HTTPRequest.h"
#include <json.hpp>

#define QUIT(request, code) {\
    request.sendResponseHeaders(code);\
    return;\
}

#define QUIT_MSG(request, code, msg) {\
    request.sendResponseHeaders(code);\
    request.getStream() << msg;\
    return;\
}

#define QUIT_JSON(request, code, json) {\
    vmc::util::sendJSON(request, json, code);\
    return;\
}

#define QUIT_BAD_REQUEST(request) {\
    QUIT_MSG(request, 400, "{ \"okay\": false, \"error\": \"Bad request\" }");\
}

#define ASSERT_JSON_KEY(request, key) {\
    if (!request.getPostData().hasJsonData()) QUIT_BAD_REQUEST(request.getRequest());\
    if (request.getPostData().getJson().count(key) == 0) QUIT_BAD_REQUEST(request.getRequest());\
}

namespace vmc
{
    namespace util
    {
        char const *getStatus(int code);
        void redirect(HTTPRequest &req, std::string const &location);
        void sendJSON(HTTPRequest &req, nlohmann::json const &json, int code = 200);
    }
}

#endif
