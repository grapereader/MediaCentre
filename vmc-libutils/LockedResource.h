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
#ifndef LOCKEDRESOURCE_H
#define LOCKEDRESOURCE_H

#include <mutex>

namespace vmc
{
    template <typename T>
    class LockedResource
    {
    public:
        LockedResource(T *resource, std::mutex *mutex) : resource(resource), mutex(mutex)
        {
            this->mutex->lock();
        }

        ~LockedResource()
        {
            this->mutex->unlock();
        }

        T *operator->()
        {
            return resource;
        }

        T const *operator->() const
        {
            return resource;
        }

    private:
        T *resource;
        std::mutex *mutex;
    };
}

#endif
