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
