#include "ThreadPool.h"

#include <iostream>

namespace vmc
{
    PoolThread::PoolThread(std::function<void(void)> const &func)
    {
        this->done = new std::atomic<bool>(false);
        auto donePtr = this->done;
        this->thread = std::unique_ptr<std::thread>(new std::thread([donePtr, &func] {
            func();
            *donePtr = true;
        }));
    }

    PoolThread::~PoolThread()
    {
        delete this->done;
    }

    std::atomic<bool> const *PoolThread::isDone() const { return this->done; }

    ThreadPool::ThreadPool(int threads)
    {
        this->threadCount = threads;
        this->threads = std::unique_ptr<std::vector<PoolThread>>(new std::vector<PoolThread>());
    }

    void ThreadPool::task(std::function<void(void)> const &func)
    {
        std::cout << "Thread pool currently using " << this->threads->size() << "/" << this->threadCount << " threads" << std::endl;
        while (this->threads->size() >= this->threadCount)
        {
            for (std::vector<PoolThread>::iterator iter = this->threads->begin(); iter != this->threads->end(); iter++)
            {
                if (iter->isDone())
                {
                    std::cout << "Removing thread..." << std::endl;
                    this->threads->erase(iter);
                }
            }
        }
        PoolThread thread(func);
        this->threads->push_back(thread);
    }
}
