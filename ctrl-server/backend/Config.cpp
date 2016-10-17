#include "Config.h"

#include <boost/filesystem.hpp>
#include <fstream>

namespace vmc
{
    auto defaultConfig = R"(
    {
        "http": {
            "host": "0.0.0.0",
            "port": 8080
        },
        "database": {
            "host": "localhost",
            "port": 3306,
            "user": "username",
            "pass": "password",
            "database": "vmc"
        }
    }
    )";

    Config::Config(char const *path)
    {
        std::ifstream cfile(path);
        if (cfile)
        {
            this->configData = json::parse(cfile);
            std::cout << "Loading config from \"" << path << "\"" << std::endl;
        }
        else
        {
            std::cout << "Could not load config file. Saving default config..." << std::endl;
            auto dirs = boost::filesystem::path(path).parent_path();
            try
            {
                boost::filesystem::create_directories(dirs);
            }
            catch (std::runtime_error e)
            {
                std::cout << "Error creating directories for config" << std::endl;
            }

            std::ofstream out(path);
            if (out)
            {
                out << defaultConfig;
                out.close();
            }
            else
            {
                std::cout << "Could not write config file" << std::endl;
            }

            std::stringstream stream;
            stream << defaultConfig;
            this->configData = json::parse(stream);
        }
    }

    json const &Config::get() const
    {
        return this->configData;
    }
}
