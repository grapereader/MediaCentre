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
