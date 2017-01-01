#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <vector>

#include "Input.h"

namespace vmc
{
    namespace input
    {
        class InputManager
        {
        public:
            InputManager();

            void setCurrentInput(size_t id);
            size_t getCurrentInput() const;
            std::vector<Input> const &getInputs() const;
        private:
            //TODO Runtime configurable
            std::vector<Input> inputs = {
                Input("Raspberry Pi", 0),
                Input("TV Out", 0),
                Input("Aux", 0)
            };

            size_t currentInput;
        };
    }
}

#endif
