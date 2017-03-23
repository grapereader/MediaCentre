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
#include "InputRoutes.h"

#include "AuthRoutes.h"

#include <vmc-libhttp/HTTPUtils.h>

#define PL1 std::placeholders::_1

using json = nlohmann::json;

namespace vmc
{
    namespace routes
    {
        InputRoutes::InputRoutes(Config const *config, input::InputManager *inputManager) : RouteGroup(config)
        {
            this->inputManager = inputManager;
        }

        void InputRoutes::initRoutes(Router &router)
        {
            router.route({method::GET}, "/getInputs", std::bind(&InputRoutes::getInputs, this, PL1));
            router.route({method::POST}, "/setInput", std::bind(&InputRoutes::setInput, this, PL1));
        }

        void InputRoutes::getInputs(RouterRequest &request)
        {
            auto session = request.initSession();
            ASSERT_ACCESS(request, session, ACCESS_GUEST);
            json responseJson = {};
            responseJson["okay"] = true;

            json inputArr = json::array();

            auto inputs = &this->inputManager->getInputs();

            for (size_t i = 0; i < inputs->size(); i++)
            {
                auto input = &inputs->at(i);
                inputArr.push_back({
                    {"id", i},
                    {"name", input->getName()}
                });
            }

            responseJson["inputs"] = inputArr;
            responseJson["currentInput"] = this->inputManager->getCurrentInput();

            util::sendJSON(request.getRequest(), responseJson);
        }

        void InputRoutes::setInput(RouterRequest &request)
        {
            auto session = request.initSession();
            ASSERT_ACCESS(request, session, ACCESS_MEMBER);
            ASSERT_JSON_KEY(request, "id");
            size_t id = request.getPostData().getJson()["id"];

            this->inputManager->setCurrentInput(id);

            json responseJson = {{"okay", true}};
            responseJson["currentInput"] = id;

            util::sendJSON(request.getRequest(), responseJson);
        }
    }
}
