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
