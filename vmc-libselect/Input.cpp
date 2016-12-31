#include "Input.h"

namespace vmc
{
    namespace input
    {
        Input::Input(std::string const &name, int gpioPin)
        {
            this->name = name;
            this->gpioPin = gpioPin;
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
