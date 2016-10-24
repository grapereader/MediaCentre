#include "StreamManager.h"

#include <exception>

namespace vmc
{
    StreamManager::StreamManager()
    {
    }

    void StreamManager::play(std::unique_ptr<Stream> stream)
    {
        std::lock_guard<std::mutex> lock(this->streamMutex);
        if (this->currentStream) this->currentStream->stop();
        this->currentStream = std::move(stream);
        this->currentStream->start();
    }

    LockedResource<Stream> StreamManager::getStream()
    {
        return LockedResource<Stream>(this->currentStream.get(), &this->streamMutex);
    }
}
