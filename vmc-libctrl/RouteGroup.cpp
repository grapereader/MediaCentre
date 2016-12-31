#include "RouteGroup.h"

namespace vmc
{
    RouteGroup::RouteGroup(Config const *config)
    {
        this->config = config;
    }

    Config const *RouteGroup::getConfig() const
    {
        return this->config;
    }
}
