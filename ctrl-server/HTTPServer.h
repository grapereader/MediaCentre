#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <string>
#include <functional>

namespace vmc
{
    class HTTPServer
    {
    public:
        HTTPServer(std::string const &host, int port);
        void listen(std::function<void(void)> func);
    private:
        std::string host;
        int port;
    };
}
#endif
