#include "InputManager.h"

namespace vmc
{
    namespace input
    {
        InputManager::InputManager()
        {}

        std::vector<Input> const &InputManager::getInputs() const
        {
            return this->inputs;
        }
    }
}
