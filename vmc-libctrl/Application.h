#ifndef APPLICATION_H
#define APPLICATION_H

#include <vmc-libutils/Config.h>
#include <vmc-libselect/InputManager.h>
#include <vmc-libstream/PlaylistManager.h>

namespace vmc
{
    namespace ctrl
    {
        void start(Config const *config, input::InputManager *inputManager, stream::PlaylistManager *playlistManager);
    }
}

#endif
