#include "Config.h"

#include <boost/filesystem.hpp>
#include <fstream>

namespace vmc
{
    Config::Config(char const *path, json const &defaultConfig)
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
                out << defaultConfig.dump(4);
                out.close();
            }
            else
            {
                std::cout << "Could not write config file" << std::endl;
            }

            this->configData = defaultConfig;
        }
    }

    json const &Config::get() const
    {
        return this->configData;
    }
}
