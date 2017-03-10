#include "Utils.h"

#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <array>

namespace vmc
{
    namespace utils
    {
        std::string callProcess(const char* cmd) {
            std::array<char, 128> buffer;
            std::string result;
            std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
            if (!pipe) throw std::runtime_error("Unable to call popen");
            while (!feof(pipe.get())) {
                if (fgets(buffer.data(), 128, pipe.get()) != NULL)
                    result += buffer.data();
            }
            return result;
        }
    }
}
