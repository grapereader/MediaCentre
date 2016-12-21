#include "AppUtils.h"

namespace vmc
{
    namespace utils
    {
        bool jsonHasKeys(json const &jsonData, std::initializer_list<std::string> keys)
        {
            for (auto it = keys.begin(); it != keys.end(); it++)
            {
                if (jsonData.count(*it) == 0) return false;
            }
            return true;
        }
    }

    namespace string
    {
        bool isAlphaNumeric(std::string const &str)
        {
            for (auto it = str.begin(); it != str.end(); it++)
            {
                if (!std::isalnum(*it)) return false;
            }
            return true;
        }
    }
}
