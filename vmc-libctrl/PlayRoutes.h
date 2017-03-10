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

            void clearPlaylist(RouterRequest &request);

            void next(RouterRequest &request);
            void back(RouterRequest &request);

            void pause(RouterRequest &request);
            void play(RouterRequest &request);

            stream::PlaylistManager *playlistManager;
        };
    }
}

#endif
