#ifndef AUTH_H
#define AUTH_H

#include <string>

namespace vmc
{
    namespace auth
    {
        std::string createHash(std::string const &password);
        bool comparePassword(std::string const &hash, std::string const &password);
    }
}

#endif
