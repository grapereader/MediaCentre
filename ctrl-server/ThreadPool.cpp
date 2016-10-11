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
