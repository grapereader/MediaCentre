#include "AudioBackend.h"

#include <giomm.h>

namespace vmc
{
    namespace stream
    {
        class OmxBackend : AudioBackend
        {
        public:
            OmxBackend();

            void play(std::string const &file) override;
            void play(InStreamPtr inputStream) override;

            void pause() override;
            void stop() override;

            void setVolume(float percent) override;
            float getVolume() const override;

            bool isSeekable() const override;
            bool isControllable() const override;

            void setPosition(int seconds) override;
            void forward(int seconds) override;
            void backward(int seconds) override;

            int getLength() const override;
        private:
            Glib::RefPtr<Gio::DBus::Connection> connection;
            Glib::RefPtr<Gio::DBus::Proxy> proxy;
            Glib::RefPtr<Gio::DBus::Proxy> playerProxy;
        };
    }
}
