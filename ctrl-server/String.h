#ifndef STRING_H
#define STRING_H

#include <vector>
#include <string>

namespace vmc
{
    namespace string
    {
        std::vector<std::string> split(std::string const &str, std::string const &delim);
        std::vector<std::string> split(std::string const &str, std::string const &delim, int count);
        std::string trim(std::string const &str);
        std::string replace(std::string const &str, std::string const &what, std::string const &with);
        std::string replace(std::string const &str, std::string const &what, std::string const &with, int count);
        
    }
}

#endif
