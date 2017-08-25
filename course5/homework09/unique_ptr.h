#pragma once
#include <cstdlib>
#include <utility>

template<class T>
struct remove_extent { typedef T type; };

template<class T>
struct remove_extent<T[]> { typedef T type; };

template<class T, std::size_t N>
struct remove_extent<T[N]> { typedef T type; };

template<typename T>
class UniquePtr;

template<typename T, typename ...Args>
UniquePtr<T> MakeUnique(Args&& ... args)
{
    return UniquePtr<T>(new T(std::forward<Args>(args)...));
}

template<typename T>
UniquePtr<T> MakeUnique(std::size_t size)
{
    return UniquePtr<T>(new typename remove_extent<T>::type[size]());
}

template<typename T>
class UniquePtr
{
public:
    UniquePtr() = default;

    UniquePtr(T* pointer) : pointer(pointer)
    {}

    UniquePtr(UniquePtr && unique_ptr)
    {
        this->pointer = unique_ptr.pointer;
        unique_ptr.pointer = nullptr;
    }

    ~UniquePtr()
    {
        if (pointer)
            delete pointer;
    }

    UniquePtr& operator=(const UniquePtr&) = delete;

    UniquePtr & operator = (UniquePtr && other)
    {
        if (this->pointer)
            delete this->pointer;
        this->pointer = other.pointer;
        other.pointer = nullptr;
    }

    T* release()
    {
        auto p = this->pointer;
        this->pointer = nullptr;
        return p;
    }

    void reset(T* ptr = nullptr)
    {
        if (this->pointer)
            delete this->pointer;
        this->pointer = ptr;
    }

    void swap(UniquePtr & other)
    {
        auto p = this->pointer;
        this->pointer = other.pointer;
        other.pointer = p;
    }

    T* get() const
    {
        return this->pointer;
    }

    operator bool() const
    {
        return (this->pointer != nullptr);
    }

    T& operator[](std::size_t i) const
    {
        return get()[i];
    }

    T* operator->() const
    {
        return get();
    }

    bool operator == (UniquePtr<T> other) const
    {
        return other.pointer == this->pointer;
    }

    bool operator != (UniquePtr<T> other) const
    {
        return other.pointer != this->pointer;
    }

private:
    T* pointer = nullptr;
};
