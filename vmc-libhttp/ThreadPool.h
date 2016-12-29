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
