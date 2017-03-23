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
#include "IO.h"

#include <fstream>
#include <boost/filesystem.hpp>

#define COPY_BUFFER_LEN 4096

namespace vmc
{
    namespace io
    {
        std::istream &getLineNoReturn(std::istream &stream, std::string &string)
        {
            std::getline(stream, string);
            string.assign(string::replace(string, "\r", ""));
            return stream;
        }

        void writeFileToStream(std::string const &path, std::ostream &stream)
        {
            std::ifstream file(path, std::ifstream::binary);
            char *buffer = new char[COPY_BUFFER_LEN];

            while (!file.eof())
            {
                file.read(buffer, COPY_BUFFER_LEN);
                auto read = file.gcount();
                stream.write(buffer, read);
            }

            delete[] buffer;
        }

        std::size_t getFileSize(std::string const &path)
        {
            std::ifstream file(path);
            file.seekg(0, std::ios_base::end);
            return file.tellg();
        }

        bool fileExists(std::string const &path)
        {
            return boost::filesystem::is_regular(boost::filesystem::path(path));
        }
    }
}
