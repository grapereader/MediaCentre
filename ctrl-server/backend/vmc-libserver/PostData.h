#ifndef POSTDATA_H
#define POSTDATA_H

#include <unordered_map>
#include <string>
#include <json.hpp>

using json = nlohmann::json;

namespace vmc
{
    class PostData
    {
    public:
        PostData();
        void setJson(json const &jsonData);
        void setUrl(std::unordered_map<std::string, std::string> const &urlData);
        json const &getJson() const;
        std::unordered_map<std::string, std::string> const &getUrlParams() const;
        bool hasJsonData() const;
        bool hasUrlData() const;
    private:
        bool hasJson;
        bool hasUrl;
        json jsonData;
        std::unordered_map<std::string, std::string> urlData;
    };
}

#endif
