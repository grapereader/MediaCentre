#ifndef APPUTILS_H
#define APPUTILS_H

#include <json.hpp>

using json = nlohmann::json;

namespace vmc
{
    namespace utils
    {
        bool jsonHasKeys(json const &jsonData, std::initializer_list<std::string> keys);
    }

    namespace string
    {
        bool isAlphaNumeric(std::string const &str);
    }
}

#endif
