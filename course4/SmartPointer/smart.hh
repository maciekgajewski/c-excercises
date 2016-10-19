#pragma once
#include <ostream>
#include <memory>

namespace course {

template<class T>
class uniquePtr
{
private:
    T* mPtr;
public:
    uniquePtr()
        :mPtr(nullptr)
    {}

    uniquePtr(T* p)
        :mPtr(p)
    {}

    // disable copy
    uniquePtr(const uniquePtr& copy) = delete;

    uniquePtr(uniquePtr&& u)
    {
        mPtr = u.mPtr;
        u.mPtr = nullptr;
    }

    ~uniquePtr()
    {
        delete mPtr;
        mPtr = nullptr;
    }

    T& operator*()
    {
        return *mPtr;
    }

    T* operator->()
    {
        return mPtr;
    }

    T* get() const
    {
        return mPtr;
    }

    void release()
    {
        mPtr = nullptr;
    }

};

}

