#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <memory>
#include <boost/asio.hpp>
#include "HTTPHeaders.h"
#include "SessionManager.h"
#include "PostData.h"

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
        HTTPRequest(method::HTTPMethod method, std::string const &resource, std::shared_ptr<HTTPHeaders> headers, tcp::iostream *stream, std::shared_ptr<SessionManager> sessionManager);
        method::HTTPMethod getMethod() const;
        std::string const &getResource() const;
        HTTPHeaders const &getHeaders() const;
        std::shared_ptr<HTTPHeaders> getResponseHeaders();
        std::shared_ptr<Session> initSession();
        void sendResponseHeaders(int code);
        tcp::iostream &getStream();
        bool hasPostData() const;
        PostData const *getPostData() const;
        void setPostData(std::unique_ptr<PostData> postData);
    private:
        method::HTTPMethod method;
        std::string resource;
        std::shared_ptr<HTTPHeaders> headers;
        std::shared_ptr<HTTPHeaders> responseHeaders;
        tcp::iostream *stream;
        std::shared_ptr<SessionManager> sessionManager;
        bool _hasPostData;
        std::unique_ptr<PostData> postData;
    };
}

#endif
