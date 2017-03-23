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
#include "Input.h"

#include <iostream>

namespace vmc
{
    namespace input
    {
        Input::Input(std::string const &name, int gpioPin)
        {
            this->name = name;
            this->gpioPin = gpioPin;
        }

        void Input::setEnabled(bool enabled)
        {
            std::cout << "TODO: Input " << this->name << " setEnabled called (" << enabled << ")" << std::endl;
        }

        std::string const &Input::getName() const
        {
            return this->name;
        }

        int Input::getGpioPin() const
        {
            return this->gpioPin;
        }
    }
}
