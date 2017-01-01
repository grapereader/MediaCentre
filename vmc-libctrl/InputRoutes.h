#ifndef INPUTROUTES_H
#define INPUTROUTES_H

#include "RouteGroup.h"

namespace vmc
{
    namespace routes
    {
        class InputRoutes : public RouteGroup
        {
        public:
            InputRoutes(Config const *config) : RouteGroup(config) {}

            void initRoutes(Router &router) override;
        private:
            void getInputs(RouterRequest &request);
            void setInput(RouterRequest &request);
        };
    }
}

#endif
