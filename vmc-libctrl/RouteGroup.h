#ifndef ROUTEGROUP_H
#define ROUTEGROUP_H

#include <vmc-libutils/Config.h>
#include <vmc-libhttp/Router.h>

namespace vmc
{
    class RouteGroup
    {
    public:
        RouteGroup(Config const *config);

        virtual void initRoutes(Router &router) = 0;

    protected:
        Config const *getConfig() const;

    private:
        Config const *config;
    };
}

#endif
