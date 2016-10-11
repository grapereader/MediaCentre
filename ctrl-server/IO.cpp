#include "IO.h"

namespace vmc
{
    namespace io
    {
        std::istream &getLineNoReturn(std::istream &stream, std::string &string)        
        {
            std::getline(stream, string);
            string.assign(string::replace(string, "\r", ""));
            return stream;
        }
    }
}
