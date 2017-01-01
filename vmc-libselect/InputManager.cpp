#include "InputManager.h"

#include <limits>

#define NONE std::numeric_limits<size_t>::max()

namespace vmc
{
    namespace input
    {
        InputManager::InputManager()
        {
            for (auto it = this->inputs.begin(); it != this->inputs.end(); it++)
            {
                it->setEnabled(false);
            }
            this->currentInput = NONE;
            this->setCurrentInput(0);
        }

        std::vector<Input> const &InputManager::getInputs() const
        {
            return this->inputs;
        }

        void InputManager::setCurrentInput(size_t id)
        {
            if (this->currentInput != NONE) this->inputs.at(this->currentInput).setEnabled(false);
            this->inputs.at(id).setEnabled(true);
            this->currentInput = id;
        }

        size_t InputManager::getCurrentInput() const
        {
            return this->currentInput;
        }
    }
}
