/*
 * Copyright 2017 Seth Traverse
 *
 * This file is part of ViaWare Media Centre.
 *
 * ViaWare Media Centre is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ViaWare Media Centre is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * with ViaWare Media Centre.  If not, see <http://www.gnu.org/licenses/>.
 */
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
