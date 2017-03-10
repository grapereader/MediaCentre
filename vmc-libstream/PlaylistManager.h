#ifndef PLAYLISTMANAGER_H
#define PLAYLISTMANAGER_H

#include <vector>

#include "PlaylistEntry.h"
#include "AudioBackend.h"

namespace vmc
{
    namespace stream
    {
        class PlaylistManager
        {
        public:
            PlaylistManager(std::unique_ptr<AudioBackend> backend);

            AudioBackend &getBackend();

            virtual void addEntry(PlaylistEntry const &entry) = 0;
            virtual void addEntryUpNext(PlaylistEntry const &entry) = 0;
            virtual void removeEntry(int index) = 0;
            virtual void clearAll() = 0;
            virtual void next() = 0;
            virtual void prev() = 0;
            virtual void playAtIndex(int index) = 0;
            virtual std::vector<PlaylistEntry> getPlaylist() const = 0;
        private:
            std::unique_ptr<AudioBackend> backend;
        };
    }
}

#endif
