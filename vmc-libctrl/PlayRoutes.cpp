#include "PlayRoutes.h"

#include "AuthRoutes.h"
#include <vmc-libhttp/HTTPUtils.h>
#include <vmc-libstream/Stream.h>
#include <vmc-libhttp/String.h>

#define PL1 std::placeholders::_1

namespace vmc
{
    namespace routes
    {
        PlayRoutes::PlayRoutes(Config const *config, stream::PlaylistManager *playlistManager) : RouteGroup(config)
        {
            this->playlistManager = playlistManager;
        }

        void PlayRoutes::initRoutes(Router &router)
        {
            router.route({vmc::method::POST}, "/addMediaUrl", std::bind(&PlayRoutes::addMediaUrl, this, PL1));
            router.route({vmc::method::POST}, "/addMediaUpload", std::bind(&PlayRoutes::addMediaUpload, this, PL1));
            router.route({vmc::method::GET}, "/playerState", std::bind(&PlayRoutes::getPlayerState, this, PL1));
        }

        void PlayRoutes::addMediaUrl(RouterRequest &request)
        {
            auto session = request.initSession();
            ASSERT_ACCESS(request, session, ACCESS_GUEST);
            ASSERT_JSON_KEY(request, "insertType");
            ASSERT_JSON_KEY(request, "url");

            json requestJson = request.getPostData().getJson();
            json responseJson = {};
            responseJson["okay"] = true;

            std::string insertType = requestJson["insertType"];
            std::string url = requestJson["url"];

            stream::Stream stream(url);
            auto entry = stream.getEntry();

            if (string::contains(insertType, "next"))
            {
                this->playlistManager->addEntryUpNext(*entry);
            }
            else if (string::contains(insertType, "back"))
            {
                this->playlistManager->addEntry(*entry);
            }

            util::sendJSON(request.getRequest(), responseJson);
        }

        void PlayRoutes::addMediaUpload(RouterRequest &request)
        {
            QUIT_MSG(request.getRequest(), 404, "Not implemented");
        }

        void PlayRoutes::getPlayerState(RouterRequest &request)
        {
            auto session = request.initSession();
            ASSERT_ACCESS(request, session, ACCESS_GUEST);

            json responseJson = {};

            auto *backend = &this->playlistManager->getBackend();

            responseJson["seekable"] = backend->isSeekable();
            responseJson["controllable"] = backend->isControllable();
            responseJson["length"] = backend->getLength();
            responseJson["volume"] = backend->getVolume();

            util::sendJSON(request.getRequest(), responseJson);
        }
    }
}
