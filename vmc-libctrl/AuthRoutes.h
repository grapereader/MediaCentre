#ifndef AUTHROUTES_H
#define AUTHROUTES_H

#include <vmc-libhttp/Router.h>
#include <vmc-libutils/Config.h>

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
