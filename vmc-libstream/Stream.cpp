#include "Stream.h"

#include <exception>

namespace vmc
{
    namespace stream
    {
        Stream::Stream(type::StreamType type, std::string const &path)
        {
            this->type = type;
            this->path = path;
        }

        void Stream::load()
        {

        }

        void Stream::start(AudioBackend &backend)
        {

        }
    }
}
