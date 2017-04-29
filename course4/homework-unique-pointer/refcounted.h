#pragma once
#include<iostream>

namespace course{

template <typename T>
class RefcountingPointer
{
private:
    T* payload;
    uint16_t* count;
    RefcountingPointer() = default;

    void decrement()
    {
        if(count == nullptr)
        {
            return;
        }

        if(--(*count) == 0)
        {
            delete payload;
            delete count;
            count = nullptr;
        }
    }

public:

    RefcountingPointer(const RefcountingPointer& other)
    {
        payload = other.payload;
        count = other.count;
        (*count)++;
    }

    RefcountingPointer(RefcountingPointer&& other)
    {
        payload = other.payload;
        count = other.count;
        other.payload = nullptr;
        other.count = nullptr;
    }

    ~RefcountingPointer()
    {
       decrement();
    }

    T& get()
    {
        return *payload;
    }

    T& operator*()
    {
        return *payload;
    }

    T *operator->() const
    {
        return payload;
    }

    const uint getCount() const
    {
        return *count;
    }

    RefcountingPointer& operator=(const RefcountingPointer& other)
    {
        decrement();
        count = other.count;
        payload = other.payload;
        (*count)++;
        return *this;
    }

    RefcountingPointer& operator=(RefcountingPointer&& other)
    {
        decrement();
        count = other.count;
        payload = other.payload;
        other.payload = nullptr;
        other.count = nullptr;
        return *this;
    }

    template<typename...TArgs>
    static RefcountingPointer<T> createInstance(TArgs...args)
    {
        RefcountingPointer<T> result;
        result.payload = new T(args...);
        result.count = new uint16_t(1);
        return result;
    }
};
}
