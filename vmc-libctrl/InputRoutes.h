#ifndef INPUTROUTES_H
#define INPUTROUTES_H

#include "RouteGroup.h"

#include <vmc-libselect/InputManager.h>

namespace vmc
{
    namespace routes
    {
        class InputRoutes : public RouteGroup
        {
        public:
            InputRoutes(Config const *config, input::InputManager *inputManager);

            void initRoutes(Router &router) override;
        private:
            void getInputs(RouterRequest &request);
            void setInput(RouterRequest &request);

            input::InputManager *inputManager;
        };
    }
}

#endif
