#include "PostData.h"

namespace vmc
{
    PostData::PostData()
    {
        this->hasJson = false;
        this->hasUrl = false;
    }

    void PostData::setJson(json const &jsonData)
    {
        this->hasJson = true;
        this->jsonData = jsonData;
    }

    void PostData::setUrl(std::unordered_map<std::string, std::string> const &urlData)
    {
        this->hasUrl = true;
        this->urlData = urlData;
    }

    json const &PostData::getJson() const
    {
        return this->jsonData;
    }

    std::unordered_map<std::string, std::string> const &PostData::getUrlParams() const
    {
        return this->urlData;
    }

    bool PostData::hasJsonData() const
    {
        return this->hasJson;
    }

    bool PostData::hasUrlData() const
    {
        return this->hasUrl;
    }
}
