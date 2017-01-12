#include "OmxBackend.h"

#include <cstdlib>

namespace vmc
{
    namespace stream
    {
        OmxBackend::OmxBackend()
        {
            this->connection = Gio::DBus::Connection::get_sync(Gio::DBus::BUS_TYPE_SESSION);
            this->proxy = Gio::DBus::Proxy::create_sync(this->connection, "org.mpris.MediaPlayer2",
                "/org/mpris/MediaPlayer2", "org.mpris.MediaPlayer2", Gio::Cancellable::create());
            this->playerProxy = Gio::DBus::Proxy::create_sync(this->connection, "org.mpris.MediaPlayer2.Player",
                "/org/mpris/MediaPlayer2/Player", "org.mpris.MediaPlayer2.Player", Gio::Cancellable::create());
        }

        void OmxBackend::play(std::string const &file)
        {
            std::system(std::string("omxplayer -o local ").append(file).c_str());
        }

        void OmxBackend::play(InStreamPtr stream)
        {
        }

        void OmxBackend::pause()
        {
            this->playerProxy->call_sync("Pause");
        }

        void OmxBackend::stop()
        {
            this->playerProxy->call_sync("Stop");
        }

        void OmxBackend::setVolume(float percent)
        {
            auto params = Glib::VariantContainerBase::create_tuple(Glib::Variant<double>::create(percent));
            this->playerProxy->call_sync("Volume", params);
        }

        float OmxBackend::getVolume() const
        {
            auto response = this->playerProxy->call_sync("Volume");
            return Glib::VariantBase::cast_dynamic<double>(response.get_child());
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
