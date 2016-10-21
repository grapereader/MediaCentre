#ifndef HTTPUTILS_H
#define HTTPUTILS_H

#include <string>
#include "HTTPRequest.h"

namespace vmc
{
    namespace util
    {
        char const *getStatus(int code);
        void redirect(HTTPRequest &req, std::string const &location);
    }
}

#endif
