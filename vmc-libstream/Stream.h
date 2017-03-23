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
#ifndef STREAM_H
#define STREAM_H

#include <string>
#include <memory>

#include "AudioBackend.h"
#include "PlaylistEntry.h"

namespace vmc
{
    namespace stream
    {
        namespace type
        {
            enum StreamType
            {
                YOUTUBE,
                HTTP,
                LOCAL_FILE
            };
        }

        class Stream
        {
        public:
            Stream(std::string const &path);
            Stream(std::string const &path, type::StreamType type);

            std::shared_ptr<PlaylistEntry> getEntry() const;
        private:
            std::string getUrl() const;
            type::StreamType type;
            std::string path;
        };
    }
}

#endif
