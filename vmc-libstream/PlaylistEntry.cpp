#include "PlaylistEntry.h"

namespace vmc
{
    namespace stream
    {
        PlaylistEntry::PlaylistEntry(std::string const &url, std::string const &title, int id)
        {
            this->url = url;
            this->id = id;
            this->title = title;
        }

        std::string const &PlaylistEntry::getUrl() const
        {
            return this->url;
        }

        std::string const &PlaylistEntry::getTitle() const
        {
            return this->title;
        }

        int PlaylistEntry::getId() const
        {
            return this->id;
        }

    }
}
