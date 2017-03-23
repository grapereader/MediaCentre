/*
 * Copyright 2017 Seth Traverse
 *
 * This file is part of ViaWare Media Centre.
 *
 * ViaWare Media Centre is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ViaWare Media Centre is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * with ViaWare Media Centre.  If not, see <http://www.gnu.org/licenses/>.
 */
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
