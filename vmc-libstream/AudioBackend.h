#ifndef AUDIOBACKEND_H
#define AUDIOBACKEND_H

#include <string>
#include <memory>
#include <istream>

namespace vmc
{
    namespace stream
    {
        typedef std::unique_ptr<std::istream> InStreamPtr;

        class AudioBackend
        {
        public:
            virtual void play(std::string const &file) = 0;
            virtual void play(InStreamPtr inputStream) = 0;

            virtual void pause() = 0;
            virtual void stop() = 0;

            virtual void setVolume(float percent) = 0;
            virtual float getVolume() const = 0;

            virtual bool isSeekable() const = 0;
            virtual bool isControllable() const = 0;

            virtual void setPosition(int seconds) = 0;
            virtual void forward(int seconds) = 0;
            virtual void backward(int seconds) = 0;

            virtual int getLength() const = 0;
        };
    }
}

#endif
