#ifndef AUTHROUTES_H
#define AUTHROUTES_H

#include <vmc-libhttp/Router.h>
#include <vmc-libutils/Config.h>

#include "RouteGroup.h"

#define ACCESS_GUEST 1
#define ACCESS_MEMBER 2
#define ACCESS_ADMIN 3

#define AUTHENTICATED(session) (session->exists("authenticated") && session->get<bool>("authenticated"))
#define HAS_ACCESS(session, priv) (AUTHENTICATED(session) && session->get<int>("access-level") >= priv)
#define ASSERT_ACCESS(request, session, priv) {\
    if (!HAS_ACCESS(session, priv)) QUIT_MSG(request.getRequest(), 403, "Forbidden");\
}

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
