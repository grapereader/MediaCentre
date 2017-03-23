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
