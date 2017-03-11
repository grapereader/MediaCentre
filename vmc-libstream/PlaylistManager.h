#ifndef PLAYLISTMANAGER_H
#define PLAYLISTMANAGER_H

#include <vector>

#include "PlaylistEntry.h"
#include "AudioBackend.h"

namespace vmc
{
    namespace stream
    {
        typedef struct PositionInfo
        {
            int position;
            int length;
        } PositionInfo;

        typedef struct Playlist
        {
            int nowPlaying;
            std::vector<PlaylistEntry> entries;
        } Playlist;

        namespace state
        {
            enum PlayState
            {
                PAUSED, PLAYING, STOPPED
            };
        }

        class PlaylistManager
        {
        public:
            PlaylistManager(std::unique_ptr<AudioBackend> backend);

            //AudioBackend &getBackend();

            virtual void addEntry(PlaylistEntry const &entry) = 0;
            virtual void addEntryUpNext(PlaylistEntry const &entry) = 0;
            virtual void removeEntry(int index) = 0;
            virtual void clearAll() = 0;
            virtual void next() = 0;
            virtual void prev() = 0;
            virtual void playAtIndex(int index) = 0;
            virtual Playlist getPlaylist() const = 0;

            virtual PositionInfo getPositionInfo() const = 0;
            virtual state::PlayState getPlayState() const = 0;
            virtual void setPlayState(state::PlayState state) = 0;
            virtual void setPosition(int seconds) = 0;
        private:
            std::unique_ptr<AudioBackend> backend;
        };
    }
}

#endif
