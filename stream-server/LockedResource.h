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
