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
#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#define SESSION_COOKIE "vmc-session"
#define SESSION_TOKEN_LENGTH 16
#define MAX_SESSION_AGE 12*60*60

#include <vector>
#include <memory>
#include <mutex>

#include "HTTPHeaders.h"
#include "Session.h"

namespace vmc
{
    class SessionManager
    {
    public:
        std::shared_ptr<Session> getSession(std::string const &sessionId);
        std::shared_ptr<Session> createSession();
    private:
        std::vector<std::shared_ptr<Session>> sessions;
        std::mutex sessionsMutex;
    };

    namespace session
    {
        std::shared_ptr<Session> init(SessionManager &sessionManager, HTTPHeaders const &requestHeaders, HTTPHeaders &responseHeaders);
    }
}

#endif
