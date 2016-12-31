#ifndef AUTHROUTES_H
#define AUTHROUTES_H

#include <vmc-libhttp/Router.h>
#include <vmc-libutils/Config.h>

#include "RouteGroup.h"

namespace vmc
{
    namespace routes
    {
        class AuthRoutes : public RouteGroup
        {
        public:
            AuthRoutes(Config const *config) : RouteGroup(config) {};
            void initRoutes(Router &router) override;
        private:
            void loginStatus(RouterRequest &request);
            void login(RouterRequest &request);
            void logout(RouterRequest &request);
            void registr(RouterRequest &request);
        };
    }
}
#endif
