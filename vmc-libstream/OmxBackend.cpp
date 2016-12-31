#include "OmxBackend.h"

namespace vmc
{
    namespace stream
    {
        void OmxBackend::play(std::string const &file)
        {

        }

        void OmxBackend::play(InStreamPtr stream)
        {

        }

        void OmxBackend::pause()
        {

        }

        void OmxBackend::stop()
        {

        }

        void OmxBackend::setVolume(float percent)
        {

        }

        float OmxBackend::getVolume() const
        {
            throw;
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
