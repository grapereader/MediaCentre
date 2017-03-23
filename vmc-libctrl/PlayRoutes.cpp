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
            router.route({vmc::method::POST}, "/player/addUrl", std::bind(&PlayRoutes::addMediaUrl, this, PL1));
            router.route({vmc::method::POST}, "/player/addUpload", std::bind(&PlayRoutes::addMediaUpload, this, PL1));
            router.route({vmc::method::GET},  "/player/state", std::bind(&PlayRoutes::getPlayerState, this, PL1));
            router.route({vmc::method::POST}, "/player/clear", std::bind(&PlayRoutes::clearPlaylist, this, PL1));
            router.route({vmc::method::POST}, "/player/next", std::bind(&PlayRoutes::next, this, PL1));
            router.route({vmc::method::POST}, "/player/back", std::bind(&PlayRoutes::back, this, PL1));
            router.route({vmc::method::POST}, "/player/setPlayState", std::bind(&PlayRoutes::setPlayState, this, PL1));
            router.route({vmc::method::POST}, "/player/setPosition", std::bind(&PlayRoutes::setPosition, this, PL1));
            router.route({vmc::method::GET}, "/player/getPlaylist", std::bind(&PlayRoutes::getPlaylist, this, PL1));
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

            std::string playString = "stopped";
            auto state = this->playlistManager->getPlayState();
            if (state == stream::state::PLAYING) playString = "playing";
            else if (state == stream::state::PAUSED) playString = "paused";

            responseJson["state"] = playString;

            auto position = this->playlistManager->getPositionInfo();
            responseJson["position"] = position.position;
            responseJson["length"] = position.length;

            util::sendJSON(request.getRequest(), responseJson);
        }

        void PlayRoutes::getPlaylist(RouterRequest &request)
        {
            auto session = request.initSession();
            ASSERT_ACCESS(request, session, ACCESS_GUEST);

            json responseJson = {};

            auto playlist = this->playlistManager->getPlaylist();
            responseJson["playing"] = playlist.nowPlaying;

            auto entries = playlist.entries;
            json entryList = json::array();
            for (auto it = entries.begin(); it != entries.end(); it++)
            {
                json entry = {};
                entry["title"] = it->getTitle();
                entry["id"] = it->getId();
                entryList.push_back(entry);
            }

            responseJson["okay"] = true;
            responseJson["playlist"] = entryList;
            util::sendJSON(request.getRequest(), responseJson);
        }

        void PlayRoutes::clearPlaylist(RouterRequest &request)
        {
            auto session = request.initSession();
            ASSERT_ACCESS(request, session, ACCESS_MEMBER);

            json responseJson = {};

            this->playlistManager->clearAll();

            responseJson["okay"] = true;
            util::sendJSON(request.getRequest(), responseJson);
        }

        void PlayRoutes::next(RouterRequest &request)
        {
            auto session = request.initSession();
            ASSERT_ACCESS(request, session, ACCESS_GUEST);

            json responseJson = {};

            this->playlistManager->next();

            responseJson["okay"] = true;
            util::sendJSON(request.getRequest(), responseJson);
        }

        void PlayRoutes::back(RouterRequest &request)
        {
            auto session = request.initSession();
            ASSERT_ACCESS(request, session, ACCESS_GUEST);

            json responseJson = {};

            this->playlistManager->prev();

            responseJson["okay"] = true;
            util::sendJSON(request.getRequest(), responseJson);
        }

        void PlayRoutes::setPlayState(RouterRequest &request)
        {
            auto session = request.initSession();
            ASSERT_ACCESS(request, session, ACCESS_GUEST);
            ASSERT_JSON_KEY(request, "state");

            json responseJson = {};

            std::string state = request.getPostData().getJson()["state"];
            auto playState = stream::state::STOPPED;
            if (string::contains(state, "playing")) playState = stream::state::PLAYING;
            else if (string::contains(state, "paused")) playState = stream::state::PAUSED;
            this->playlistManager->setPlayState(playState);

            playState = this->playlistManager->getPlayState();

            responseJson["okay"] = true;
            responseJson["state"] = playState == stream::state::PLAYING ? "playing" :
                playState == stream::state::PAUSED ? "paused" : "stopped";
            util::sendJSON(request.getRequest(), responseJson);
        }

        void PlayRoutes::setPosition(RouterRequest &request)
        {
            auto session = request.initSession();
            ASSERT_ACCESS(request, session, ACCESS_GUEST);
            ASSERT_JSON_KEY(request, "position");

            json responseJson = {};

            int position = request.getPostData().getJson()["position"];
            this->playlistManager->setPosition(position);

            auto posData = this->playlistManager->getPositionInfo();
            responseJson["okay"] = true;
            responseJson["position"] = posData.position;

            util::sendJSON(request.getRequest(), responseJson);
        }

    }
}
