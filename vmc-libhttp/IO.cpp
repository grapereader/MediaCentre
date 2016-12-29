#include "IO.h"

#include <fstream>
#include <boost/filesystem.hpp>

#define COPY_BUFFER_LEN 4096

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

        void writeFileToStream(std::string const &path, std::ostream &stream)
        {
            std::ifstream file(path, std::ifstream::binary);
            char *buffer = new char[COPY_BUFFER_LEN];

            while (!file.eof())
            {
                file.read(buffer, COPY_BUFFER_LEN);
                auto read = file.gcount();
                stream.write(buffer, read);
            }

            delete[] buffer;
        }

        std::size_t getFileSize(std::string const &path)
        {
            std::ifstream file(path);
            file.seekg(0, std::ios_base::end);
            return file.tellg();
        }

        bool fileExists(std::string const &path)
        {
            return boost::filesystem::is_regular(boost::filesystem::path(path));
        }
    }
}
