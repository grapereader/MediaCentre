#ifndef CONFIG_H
#define CONFIG_H

#include <json.hpp>

using json = nlohmann::json;

namespace vmc
{
    class Config
    {
    public:
        Config(char const *path);
        json const &get() const;

    private:
        json configData;
    };
}

#endif
