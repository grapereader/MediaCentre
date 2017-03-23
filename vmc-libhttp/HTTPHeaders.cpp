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
#include "HTTPHeaders.h"

#include "String.h"

namespace vmc
{
    HTTPHeaders::HTTPHeaders()
    { }

    void HTTPHeaders::put(std::string const &key, std::string const &header)
    {
        this->map[string::toUpper(key)] = header;
    }

    void HTTPHeaders::put(std::string const &key, long header)
    {
        this->map[string::toUpper(key)] = std::to_string(header);
    }

    bool HTTPHeaders::exists(std::string const &key) const
    {
        return this->map.count(string::toUpper(key));
    }

    std::string const &HTTPHeaders::get(std::string const &key) const
    {
        return this->map.at(string::toUpper(key));
    }

    void HTTPHeaders::remove(std::string const &key)
    {
        this->map.erase(string::toUpper(key));
    }

    std::unordered_map<std::string, std::string>::const_iterator HTTPHeaders::begin() const
    {
        return this->map.begin();
    }

    std::unordered_map<std::string, std::string>::const_iterator HTTPHeaders::end() const
    {
        return this->map.end();
    }
}
