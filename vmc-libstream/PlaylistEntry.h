#ifndef PLAYLISTENTRY_H
#define PLAYLISTENTRY_H

#include <string>

namespace vmc
{
    namespace stream
    {
        class PlaylistEntry
        {
        public:
            PlaylistEntry(std::string const &url, std::string const &title, int id = -1);
            std::string const &getUrl() const;
            std::string const &getTitle() const;
            int getId() const;
        private:
            std::string url;
            std::string title;
            int id;
        };
    }
}

#endif

