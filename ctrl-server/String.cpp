#include "String.h"

#include <iostream>
#include <algorithm>

namespace vmc
{
    namespace string
    {
        std::vector<std::string> split(std::string const &str, std::string const &delim)
        {
            return split(str, delim, str.length());
        }

        std::vector<std::string> split(std::string const &str, std::string const &delim, int count)
        {
            std::vector<std::string> parts;
            std::string left(str);

            int done = 0;

            while (left.length() > 0 && done++ < count)
            {
                auto index = left.find(delim);
                
                if (index == std::string::npos) break;

                std::string match = left.substr(0, index);
                left = left.substr(index + 1, left.length() - index);

                parts.push_back(match);
            }
            
            parts.push_back(left);

            return parts;
        }

        std::string trim(std::string const &str)
        {
            std::string trimmed(str);
            auto spaceEnd = trimmed.find_first_not_of(' ');
            trimmed = trimmed.substr(spaceEnd, trimmed.length() - spaceEnd);
            auto endSpace = trimmed.find_last_not_of(' ');
            trimmed = trimmed.substr(0, endSpace + 1);

            return trimmed;
        }

        std::string replace(std::string const &str, std::string const &what, std::string const &with)
        {
            return replace(str, what, with, str.length());            
        }

        std::string replace(std::string const &str, std::string const &what, std::string const &with, int count)
        {
            std::string replaced(str);

            int done = 0;
            auto location = str.find(what);
            while (location != std::string::npos && done++ < count)
            {
                replaced = replaced.replace(location, what.length(), with);
                location = replaced.find(what);
            }

            return replaced;
        }

        std::string toUpper(std::string const &str)
        {
            std::string upper(str);
            std::transform(upper.begin(), upper.end(), upper.begin(), ::toupper);
            return upper;
        }

        bool startsWith(std::string const &str, std::string const &toFind)
        {
            return str.find(toFind) == 0;
        }

        bool contains(std::string const &str, std::string const &toFind)
        {
            return str.find(toFind) != std::string::npos;
        }
    }
}
