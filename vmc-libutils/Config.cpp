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
