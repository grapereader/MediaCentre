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
#ifndef STRING_H
#define STRING_H

#include <vector>
#include <string>

namespace vmc
{
    namespace string
    {
        std::vector<std::string> split(std::string const &str, std::string const &delim);
        std::vector<std::string> split(std::string const &str, std::string const &delim, int count);
        std::string trim(std::string const &str);
        std::string replace(std::string const &str, std::string const &what, std::string const &with);
        std::string replace(std::string const &str, std::string const &what, std::string const &with, int count);
        std::string toUpper(std::string const &str);
        bool startsWith(std::string const &str, std::string const &toFind);
        bool contains(std::string const &str, std::string const &toFind);
        std::string random(int length);
        std::string random(int length, std::string const &options);
    }
}

#endif
