#ifndef INPUT_H
#define INPUT_H

#include <string>

namespace vmc
{
    namespace input
    {
        class Input
        {
        public:
            Input(std::string const &name, int gpioPin);

            //TODO Not implemented
            void setEnabled(bool enabled) = delete;

            std::string const &getName() const;
            int getGpioPin() const;
        private:
            std::string name;
            int gpioPin;
        };
    }
}

#endif
