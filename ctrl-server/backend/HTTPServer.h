#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <string>
#include <functional>

#include "HTTPRequest.h"

namespace vmc
{
    class HTTPServer
    {
        public:
        HTTPServer(std::string const &host, int port);
        void listen(std::function<void(HTTPRequest&)> func);
    private:
        std::string host;
        int port;
    };
}
#endif
