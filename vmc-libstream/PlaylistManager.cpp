#include "PlaylistManager.h"

namespace vmc
{
    namespace stream
    {
        PlaylistManager::PlaylistManager(std::unique_ptr<AudioBackend> backend)
        {
            this->backend = std::move(backend);
        }
        /*
        AudioBackend &PlaylistManager::getBackend()
        {
            return *this->backend.get();
        }
        */
    }
}
