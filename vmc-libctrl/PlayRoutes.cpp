#include "PlayRoutes.h"

#define PL1 std::placeholders::_1

namespace vmc
{
    namespace routes
    {
        PlayRoutes::PlayRoutes(Config const *config, std::unique_ptr<stream::AudioBackend> backend) : RouteGroup(config)
        {
            this->backend = std::move(backend);
        }

        void PlayRoutes::initRoutes(Router &router)
        {
            router.route({vmc::method::POST}, "/test1", std::bind(&PlayRoutes::test1, this, PL1));
            router.route({vmc::method::POST}, "/test2", std::bind(&PlayRoutes::test2, this, PL1));
        }

        void PlayRoutes::test1(RouterRequest &request)
        {
            std::cout << "Playing test file..." << std::endl;
            this->backend->play("/home/admin/video.mp4");
        }

        void PlayRoutes::test2(RouterRequest &request)
        {
            std::cout << "Stopping playback..." << std::endl;
            this->backend->stop();
        }
    }
}
