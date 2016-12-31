#ifndef STREAM_H
#define STREAM_H

#include <string>

#include "AudioBackend.h"

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

            enum LoadPolicy
            {
                SAVE_THEN_PLAY,
                STREAM
            };
        }

        class Stream
        {
        public:
            Stream(type::StreamType type, std::string const &path);

            void load();
            void start(AudioBackend &backend);
        private:
            type::StreamType type;
            std::string path;

            type::LoadPolicy loadPolicy = type::SAVE_THEN_PLAY;
        };
    }
}

#endif
