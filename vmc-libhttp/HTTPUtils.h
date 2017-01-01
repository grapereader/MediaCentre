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
