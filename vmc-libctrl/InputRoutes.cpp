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
