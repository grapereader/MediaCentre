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
        void writeFileToStream(std::string const &path, std::ostream &stream);
        std::size_t getFileSize(std::string const &path);
        bool fileExists(std::string const &path);
    }
}

#endif
