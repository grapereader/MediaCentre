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

namespace vmc
{
    namespace util
    {
        char const *getStatus(int code);
        void redirect(HTTPRequest &req, std::string const &location);
        void sendJSON(HTTPRequest &req, nlohmann::json const &json);
    }
}

#endif
