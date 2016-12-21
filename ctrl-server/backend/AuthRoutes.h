#ifndef AUTHROUTES_H
#define AUTHROUTES_H

#include "vmc-libserver/Router.h"
#include "vmc-libserver/Config.h"

namespace vmc
{
    namespace routes
    {
        namespace auth
        {
            void route(Router &router, Config const *config);
        }
    }
}
#endif
