#include "OmxBackend.h"

#include <cstdlib>
#include <iostream>

namespace vmc
{
    namespace stream
    {
        OmxBackend::OmxBackend()
        {
            Glib::init();

            const char *address = std::getenv("DBUS_SESSION_BUS_ADDRESS");
            if (!address)
            {
                std::cout << "Dbus session address not defined" << std::endl;
                throw;
            }
            std::cout << "OmxBackend: Connecting to dbus at " << address << std::endl;

            this->proxy = Gio::DBus::Proxy::create_for_bus_sync(Gio::DBus::BUS_TYPE_SESSION, "org.mpris.MediaPlayer2.omxplayer",
                "/org/mpris/MediaPlayer2", "org.mpris.MediaPlayer2");
            std::cout << "OmxBackend: Connected to mediaplayer proxy" << std::endl;

            this->playerProxy = Gio::DBus::Proxy::create_for_bus_sync(Gio::DBus::BUS_TYPE_SESSION, "org.mpris.MediaPlayer2.omxplayer",
                "/org/mpris/MediaPlayer2", "org.mpris.MediaPlayer2.Player");

            std::cout << "OmxBackend: Initialization done." << std::endl;
        }

        void OmxBackend::play(std::string const &file)
        {
            std::system(std::string("omxplayer -o local ").append(file).append(" &").c_str());
            std::cout << "OmxBackend: Playback started." << std::endl;
        }

        void OmxBackend::play(InStreamPtr stream)
        {
        }

        void OmxBackend::resume()
        {
            this->playerProxy->call_sync("Play");
        }

        void OmxBackend::pause()
        {
            this->playerProxy->call_sync("Pause");
        }

        void OmxBackend::stop()
        {
            try
            {
                this->proxy->call_sync("Quit");
            }
            catch (Glib::Error error)
            {
                std::cout << error.what() << std::endl;
            }
        }

        void OmxBackend::setVolume(float percent)
        {
            auto params = Glib::VariantContainerBase::create_tuple(Glib::Variant<double>::create(percent));
            this->playerProxy->call_sync("Volume", params);
        }

        float OmxBackend::getVolume() const
        {
            auto response = this->playerProxy->call_sync("Volume");
            auto retVal = Glib::VariantBase::cast_dynamic<Glib::Variant<double>>(response.get_child());
            return retVal.get();
        }

        bool OmxBackend::isSeekable() const
        {
            throw;
        }

        bool OmxBackend::isControllable() const
        {
            throw;
        }

        void OmxBackend::setPosition(int seconds)
        {
        }

        void OmxBackend::forward(int seconds)
        {
        }

        void OmxBackend::backward(int seconds)
        {
        }

        int OmxBackend::getLength() const
        {
            throw;
        }
    }
}
