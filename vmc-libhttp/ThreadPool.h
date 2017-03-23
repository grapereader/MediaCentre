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
#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <thread>
#include <functional>
#include <vector>
#include <atomic>
#include <memory>

namespace vmc
{
    class PoolThread
    {
    public:
        PoolThread(int id, std::function<void(void)> const &func);
        ~PoolThread();
        bool isDone() const;
        int getId() const;
    private:
        int id;
        std::thread *thread;
        std::atomic<bool> *done;
    };

    class ThreadPool
    {
    public:
        ThreadPool(unsigned int threads);
        void task(std::function<void(void)> const &func);
    private:
        unsigned int threadCount;
        int idCount;
        std::unique_ptr<std::vector<std::unique_ptr<PoolThread>>> threads;
    };
}

#endif
