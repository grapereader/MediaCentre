/*
 * Copyright 2017 Seth Traverse
 *
 * This file is part of ViaWare Media Centre.
 *
 * ViaWare Media Centre is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ViaWare Media Centre is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * with ViaWare Media Centre.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "AudioBackend.h"

#include <giomm.h>

namespace vmc
{
    namespace stream
    {
        class OmxBackend : public AudioBackend
        {
        public:
            OmxBackend();

            void play(std::string const &file) override;
            void play(InStreamPtr inputStream) override;

            void resume() override;
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

            bool running;
        };
    }
}
