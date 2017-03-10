#include "Stream.h"

#include <vmc-libutils/Utils.h>
#include <vmc-libhttp/String.h>

#include <exception>

namespace vmc
{
    namespace stream
    {
        Stream::Stream(std::string const &path, type::StreamType type)
        {
            this->type = type;
            this->path = path;
        }

        Stream::Stream(std::string const &path)
        {
            this->path = path;

            //TODO Implement detection of URLs
            this->type = type::LOCAL_FILE;

            std::string pathUpper = string::toUpper(path);
            if (string::contains(pathUpper, "YOUTUBE.COM"))
            {
                this->type = type::YOUTUBE;
            }
        }

        std::shared_ptr<PlaylistEntry> Stream::getEntry() const
        {
            return std::shared_ptr<PlaylistEntry>(new PlaylistEntry(this->getUrl()));
        }

        std::string Stream::getUrl() const {
            if (this->type == type::YOUTUBE) {
                std::string cmd = "youtube-dl -g \"";
                cmd.append(this->path).append("\"");
                std::string urlString = utils::callProcess(cmd.c_str());

                auto parts = string::split(urlString, "\n");
                if (parts.size() == 0) throw std::runtime_error("Unable to retrieve video url");

                return parts[0];
            }
            return this->path;
        }

    }
}
