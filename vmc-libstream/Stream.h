#ifndef STREAM_H
#define STREAM_H

#include <string>

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
            Stream(type::StreamType type, std::string const &path);
            void start();
            void seek(int seconds);
            void stop();

            int getLength();
            bool isSeekable();

        private:
            type::StreamType type;
            std::string path;

            bool seekable;
        };
    }
}

#endif
