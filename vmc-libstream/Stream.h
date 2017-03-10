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
