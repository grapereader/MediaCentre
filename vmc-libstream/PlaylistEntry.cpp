#include "PlaylistEntry.h"

namespace vmc
{
    namespace stream
    {
        PlaylistEntry::PlaylistEntry(std::string const &url, int id)
        {
            this->url = url;
            this->id = id;
        }

        std::string const &PlaylistEntry::getUrl() const
        {
            return this->url;
        }

        int PlaylistEntry::getId() const
        {
            return this->id;
        }

    }
}
