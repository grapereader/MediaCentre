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
#include "ThreadPool.h"

#include <iostream>

namespace vmc
{
    PoolThread::PoolThread(int id, std::function<void(void)> const &func)
    {
        this->id = id;
        this->done = new std::atomic<bool>(false);
        auto donePtr = this->done;
        this->thread = new std::thread([donePtr, &func] {
            func();
            *donePtr = true;
        });
    }

    PoolThread::~PoolThread()
    {
        delete this->done;
        this->thread->join();
        delete this->thread;
    }

    bool PoolThread::isDone() const
    {
        return this->done->load(std::memory_order_relaxed);
    }

    int PoolThread::getId() const
    {
        return this->id;
    }

    ThreadPool::ThreadPool(unsigned int threads)
    {
        this->threadCount = threads;
        this->threads = std::unique_ptr<std::vector<std::unique_ptr<PoolThread>>>(new std::vector<std::unique_ptr<PoolThread>>());
    }

    void ThreadPool::task(std::function<void(void)> const &func)
    {
        std::cout << "Thread pool currently using " << this->threads->size() << "/" << this->threadCount << " threads" << std::endl;

        do
        {
            for (auto iter = this->threads->begin(); iter != this->threads->end(); iter++)
            {
                if (iter->get()->isDone())
                {
                    std::cout << "Cleaning up thread " << iter->get()->getId() << "..." << std::endl;
                    this->threads->erase(iter);
                    break;
                }
            }
        } while (this->threads->size() >= this->threadCount);

        auto thread = std::unique_ptr<PoolThread>(new PoolThread(this->idCount++, func));
        this->threads->push_back(std::move(thread));
    }
}
