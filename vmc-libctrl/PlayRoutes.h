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
#ifndef PLAYROUTES_H
#define PLAYROUTES_H

#include <vmc-libhttp/Router.h>
#include <vmc-libstream/PlaylistManager.h>
#include "RouteGroup.h"

namespace vmc
{
    namespace routes
    {
        class PlayRoutes : public RouteGroup
        {
        public:
            PlayRoutes(Config const *config, stream::PlaylistManager *playlistManager);
            void initRoutes(Router &router);
        private:
            void addMediaUrl(RouterRequest &request);
            void addMediaUpload(RouterRequest &request);
            void getPlayerState(RouterRequest &request);

            void getPlaylist(RouterRequest &request);
            void clearPlaylist(RouterRequest &request);

            void next(RouterRequest &request);
            void back(RouterRequest &request);

            void setPlayState(RouterRequest &request);
            void setPosition(RouterRequest &request);

            stream::PlaylistManager *playlistManager;
        };
    }
}

#endif
