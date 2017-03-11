#ifndef OMXPLAYLISTMANAGER_H
#define OMXPLAYLISTMANAGER_H

#include "PlaylistManager.h"
#include "OmxBackend.h"

namespace vmc
{
    namespace stream
    {
        typedef struct OmxEntryWrapper
        {
            PlaylistEntry entry;
            long initTime;
        } OmxEntryWrapper;

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
            Playlist getPlaylist() const override;

            PositionInfo getPositionInfo() const override;
            state::PlayState getPlayState() const override;
            void setPlayState(state::PlayState state) override;
            void setPosition(int seconds) override;
        private:
            std::vector<OmxEntryWrapper> entries;
        };
    }
}

#endif
