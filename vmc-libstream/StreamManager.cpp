#include "StreamManager.h"

#include <exception>

namespace vmc
{
    namespace stream
    {
        StreamManager::StreamManager()
        {
        }

        void StreamManager::play(std::unique_ptr<Stream> stream)
        {
            std::lock_guard<std::mutex> lock(this->streamMutex);
        }

        LockedResource<Stream> StreamManager::getStream()
        {
            return LockedResource<Stream>(this->currentStream.get(), &this->streamMutex);
        }
    }
}
