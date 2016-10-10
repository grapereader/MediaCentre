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
        PoolThread(std::function<void(void)> const &func);
        ~PoolThread();
        std::atomic<bool> const *isDone() const;
    private:
        std::unique_ptr<std::thread> thread;
        std::atomic<bool> *done;
    };

    class ThreadPool
    {
    public:
        ThreadPool(int threads);
        void task(std::function<void(void)> const &func);
    private:
        int threadCount;
        std::unique_ptr<std::vector<PoolThread>> threads;
    };
}

#endif
