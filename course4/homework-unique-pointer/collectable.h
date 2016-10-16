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
        payload = std::move(other.payload);
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

    static CollectablePointer<T> createInstance()
    {
        CollectablePointer<T> result;
        result.payload = new T();
        std::cout << "allocated(): " << (void*)result.payload << std::endl;
        return result;
    }

    template<typename TArg>
    static CollectablePointer<T> createInstance(TArg arg)
    {
        CollectablePointer<T> result;
        result.payload = new T(arg);
        std::cout << "allocated(arg): "<<arg<<" " << (void*)result.payload << std::endl;
        return result;
    }

    template<typename TArg1, typename TArg2>
    static CollectablePointer<T> createInstance(TArg1 arg1, TArg2 arg2)
    {
        CollectablePointer<T> result;
        result.payload = new T(arg1, arg2);
        std::cout << "allocated(arg, arg): "<<arg1 <<" "<<arg2 <<" " << (void*)result.payload << std::endl;
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
