#pragma once
#include<iostream>
#include<vector>

namespace course{

template <typename T>
class CollectablePointer
{
private:
    T* payload;
    static std::vector<T*> poolOfDead;
    CollectablePointer() = default;

public:
    CollectablePointer(const CollectablePointer& other)
    {
        payload = new T(*other.payload);
        std::cout << "allocated as copy: " << (void*)payload << std::endl;
    }

    CollectablePointer(CollectablePointer&& other)
    {
        payload =other.payload;
        other.payload = nullptr;
    }

    ~CollectablePointer()
    {
        if(payload != nullptr)
        {
            CollectablePointer<T>::poolOfDead.push_back(payload);
            payload = nullptr;
        }
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

    template<typename...TArgs>
    static CollectablePointer<T> createInstance(TArgs...args)
    {
        CollectablePointer<T> result;
        result.payload = new T(args...);
        std::cout << "allocated(args): " << (void*)result.payload << std::endl;
        return result;
    }

    static void collect()
    {
        for(int i =0; i< CollectablePointer<T>::poolOfDead.size(); ++i)
        {
            std::cout << "Deleting: " << (void*)CollectablePointer<T>::poolOfDead[i] << std::endl;
            delete(CollectablePointer<T>::poolOfDead[i]);
        }

        CollectablePointer<T>::poolOfDead.clear();
    }

    static int itemsToCollectCount()
    {
        return CollectablePointer<T>::poolOfDead.size();
    }
};

template<typename T>
std::vector<T*> CollectablePointer<T>:: poolOfDead;
}
