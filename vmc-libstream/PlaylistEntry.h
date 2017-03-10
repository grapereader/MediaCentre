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
            PlaylistEntry(std::string const &url, int id = -1);
            std::string const &getUrl() const;
            int getId() const;
        private:
            std::string url;
            int id;
        };
    }
}

#endif

