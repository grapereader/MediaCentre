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
            std::string url = this->path;
            std::string title = this->path;
            if (this->type == type::YOUTUBE) {
                std::string cmd = "youtube-dl -e -g \"";
                cmd.append(this->path).append("\"");
                std::string urlString = utils::callProcess(cmd.c_str());

                auto parts = string::split(urlString, "\n");
                if (parts.size() < 2) throw std::runtime_error("Unable to retrieve video url");

                title = parts[0];
                url = parts[1];
            }
            return std::shared_ptr<PlaylistEntry>(new PlaylistEntry(url, title));
        }

        std::string Stream::getUrl() const {
            throw;
        }

    }
}
