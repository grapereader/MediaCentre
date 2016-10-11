#ifndef IO_H
#define IO_H

#include <istream>
#include <string>

#include "String.h"

namespace vmc
{
    namespace io
    {
        std::istream &getLineNoReturn(std::istream &stream, std::string &string);
    }
}

#endif
