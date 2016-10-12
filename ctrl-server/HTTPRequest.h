#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <memory>
#include <boost/asio.hpp>
#include "HTTPHeaders.h"

using boost::asio::ip::tcp;

namespace vmc
{

    namespace method
    {
        enum HTTPMethod
        {
            INVALID, GET, POST
        };
    }


    class HTTPRequest
    {
    public:
        HTTPRequest(method::HTTPMethod method, std::shared_ptr<HTTPHeaders> headers, tcp::iostream *stream);
        method::HTTPMethod getMethod() const;
        HTTPHeaders const *getHeaders() const;
        tcp::iostream *getStream();
    private:
        method::HTTPMethod method;
        std::shared_ptr<HTTPHeaders> headers;
        tcp::iostream *stream;
    };
}

#endif
