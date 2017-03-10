#ifndef OMXPLAYLISTMANAGER_H
#define OMXPLAYLISTMANAGER_H

#include "PlaylistManager.h"
#include "OmxBackend.h"

namespace vmc
{
    namespace stream
    {
        class OmxPlaylistManager : public PlaylistManager
        {
        public:
            OmxPlaylistManager() : PlaylistManager(std::unique_ptr<AudioBackend>(new OmxBackend())) {}

            void addEntry(PlaylistEntry const &entry) override;
            void addEntryUpNext(PlaylistEntry const &entry) override;
            void removeEntry(int index) override;
            void clearAll() override;
            void next() override;
            void prev() override;
            void playAtIndex(int index) override;
            std::vector<PlaylistEntry> getPlaylist() const override;
        };
    }
}

#endif
