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
#include "Session.h"

#include <stdint.h>
#include <exception>

namespace vmc
{

    Session::Session(std::string const &sessionId)
    {
        this->sessionId = sessionId;

        this->createdTime = std::time(nullptr);
    }

    std::time_t Session::getAge() const
    {
        return std::time(nullptr) - this->createdTime;
    }

    std::string const &Session::getSessionId() const
    {
        return this->sessionId;
    }

    bool Session::exists(std::string const &key) const
    {
        this->variablesMutex.lock();
        bool exists = this->variables.count(key);
        this->variablesMutex.unlock();
        return exists;
    }

}
