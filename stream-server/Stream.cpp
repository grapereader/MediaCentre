#include "Stream.h"

#include <exception>

namespace vmc
{
    Stream::Stream(stream::StreamType type, std::string const &path)
    {
        this->type = type;
        this->path = path;
    }

    void Stream::start()
    {
        throw std::exception();
    }

    void Stream::seek(int seconds)
    {
        throw std::exception();
    }

    void Stream::stop()
    {
        throw std::exception();
    }

    int Stream::getLength()
    {
        throw std::exception();
    }

    bool Stream::isSeekable()
    {
        return this->seekable;
    }
}
