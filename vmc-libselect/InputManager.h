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
