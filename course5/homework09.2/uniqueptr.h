#pragma once

#include <utility>

template <class Type>
class UniquePtr
{
public:
    UniquePtr() = default;
    explicit UniquePtr(Type *obj)
        : mPtr(obj)
    {}

    UniquePtr(UniquePtr &&rhs)
        : mPtr(rhs.mPtr)
    {
        rhs.mPtr = nullptr;
    }

    UniquePtr& operator=(UniquePtr &&rhs)
    {
        if (mPtr)
            delete mPtr;
        mPtr = rhs.mPtr;
        rhs.mPtr = nullptr;
        return *this;
    }

    UniquePtr(const UniquePtr &) = delete;
    UniquePtr& operator=(const UniquePtr &) = delete;

    ~UniquePtr()
    {
        reset();
    }

    void reset()
    {
        if (mPtr)
        {
            delete mPtr;
            mPtr = nullptr;
        }
    }

    Type* get()
    {
        return mPtr;
    }

    Type* operator->()
    {
        return mPtr;
    }

    Type& operator*()
    {
        return *mPtr;
    }

    bool operator==(const UniquePtr &rhs)
    {
        return mPtr == rhs.mPtr;
    }

    bool operator!=(const UniquePtr &rhs)
    {
        return mPtr != rhs.mPtr;
    }

    bool operator==(Type *rhs)
    {
        return mPtr == rhs;
    }

    bool operator!=(Type *rhs)
    {
        return mPtr != rhs;
    }

private:
    Type *mPtr = nullptr;
};

template <class Type, typename... Args>
UniquePtr<Type> MakeUnique(Args&& ...args) {
    return UniquePtr<Type>(new Type(std::forward<Args>(args))...);
}
