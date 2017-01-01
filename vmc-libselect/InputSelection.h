#ifndef INPUTSELECTION_H
#define INPUTSELECTION_H

#include "InputManager.h"

#include <iostream>

namespace vmc
{
    namespace input
    {
        void initializeInputManager();
        InputManager *getInputManager();
    }
}

#endif
