#include "OmxPlaylistManager.h"

#include <string>

namespace vmc
{
    namespace stream
    {
        void OmxPlaylistManager::addEntry(PlaylistEntry const &entry)
        {
            std::system(std::string("omxd A ").append(entry.getUrl()).c_str());
        }

        void OmxPlaylistManager::addEntryUpNext(PlaylistEntry const &entry)
        {
            std::system(std::string("omxd a ").append(entry.getUrl()).c_str());
        }

        void OmxPlaylistManager::removeEntry(int index)
        {
            std::system(std::string("omxd x ").append(std::to_string(index)).c_str());
        }

        void OmxPlaylistManager::clearAll()
        {
            std::system(std::string("omxd X").c_str());
        }

        void OmxPlaylistManager::next()
        {
            std::system(std::string("omxd n").c_str());
        }

        void OmxPlaylistManager::prev()
        {
            std::system(std::string("omxd N").c_str());
        }

        void OmxPlaylistManager::playAtIndex(int index)
        {
            std::system(std::string("omxd g ").append(std::to_string(index)).c_str());
        }

        std::vector<PlaylistEntry> OmxPlaylistManager::getPlaylist() const
        {
            throw;
        }
    }
}
