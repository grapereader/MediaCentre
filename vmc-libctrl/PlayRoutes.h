#ifndef PLAYROUTES_H
#define PLAYROUTES_H

#include <vmc-libhttp/Router.h>
#include <vmc-libstream/AudioBackend.h>
#include "RouteGroup.h"

namespace vmc
{
    namespace routes
    {
        class PlayRoutes : public RouteGroup
        {
        public:
            PlayRoutes(Config const *config, std::unique_ptr<stream::AudioBackend> backend);
            void initRoutes(Router &router);
        private:
            void test1(RouterRequest &request);
            void test2(RouterRequest &request);

            std::unique_ptr<stream::AudioBackend> backend;
        };
    }
}

#endif
