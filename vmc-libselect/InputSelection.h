#ifndef INPUTSELECTION_H
#define INPUTSELECTION_H

#include "InputManager.h"

#include <iostream>

namespace vmc
{
    namespace input
    {
        //Singleton yay (hush)
        namespace glob
        {
            InputManager *inputManager;
        }

        void initializeInputManager()
        {
            glob::inputManager = new InputManager();
            std::cout << "libselect - Input manager initialized" << std::endl;
        }

        InputManager *getInputManager()
        {
            return glob::inputManager;
        }
    }
}

#endif
