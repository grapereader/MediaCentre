/*
 * Copyright 2017 Seth Traverse
 *
 * This file is part of ViaWare Media Centre.
 *
 * ViaWare Media Centre is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ViaWare Media Centre is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * with ViaWare Media Centre.  If not, see <http://www.gnu.org/licenses/>.
 */
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
