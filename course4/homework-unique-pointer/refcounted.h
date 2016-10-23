#pragma once
#include<iostream>

namespace course{

template <typename T>
class RefcountingPointer
{
private:
    T* payload;
    uint* count;
    RefcountingPointer() = default;
    void decrement()
    {
        if(count == nullptr)
        {
            return;
        }

        if(--(*count) == 0)
        {
            std::cout << "Deleting: " << (void*)payload << std::endl;
            delete payload;
        }
        else
        {
            std::cout<<"for " <<(void*)payload <<" still " << *count <<" references" << std::endl;
        }
    }

public:

    RefcountingPointer(const RefcountingPointer& other)
    {
        payload = other.payload;
        count = other.count;
        (*count)++;
        std::cout << "allocated as copy: " << (void*)payload << ", count: "<< *count << std::endl;
    }

    RefcountingPointer(RefcountingPointer&& other)
    {
        std::cout << "move constructed" << std::endl;
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
        std::cout << "copy assigning" << std::endl;
        count = other.count;
        payload = other.payload;
        (*count)++;
        return *this;
    }

    RefcountingPointer& operator=(RefcountingPointer&& other)
    {
        decrement();
        std::cout << "move assigned" << std::endl;
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
        result.count = new uint(1);
        std::cout << "allocated(args): " << (void*)result.payload << std::endl;
        return result;
    }
};
}
