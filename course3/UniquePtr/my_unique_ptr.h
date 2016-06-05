#include <iostream>
/*
re-implemention of http://en.cppreference.com/w/cpp/memory/unique_ptr
*/

template<class T>
class MyUniquePtr
{
public:
    MyUniquePtr() = default;
    
    ~MyUniquePtr(){}
    
    MyUniquePtr(T*&& ptr) : mData(ptr)
    {
        delete ptr;
    }
    
    MyUniquePtr(T& ptr) : mData(ptr)
    {
        mData = ptr.mData;
    }
    
    // move
    MyUniquePtr(T&& ptr)
    {
        std::move(mData, ptr.mData);
    }
    
    
    MyUniquePtr& operator=(T& other)
    {
        mData = other.mData;
    }


    T *get() const
    {
        return mData;
    }

    
    T *operator->() const
    {
        return mData;
    }
    
    T operator*() const
    {
        return *mData;
    }

    T& release()
    {
        //Releases the ownership of the managed object if any. get() returns nullptr after the call.
        auto tempData = mData;
        mData = nullptr;
        return *tempData;
    }
    
    void reset(T& ptr)
    {
        //oldPtr = mData; current_ptr = ptr; if(old_ptr != nullptr) get_deleter()(old_ptr)
        auto oldPtr = mData;
        mData = ptr;
        if (oldPtr != nullptr){
            delete[] oldPtr;
        }
    }
    
    void swap(MyUniquePtr<T>& other)
    {
        std::swap(mData, other.mData);
    }

    bool operator==(T& other) const
    {
        return this->get() == other.get();
    }
    
    bool operator==(const std::nullptr_t other) const
    {
        return mData == other;
    }
    
    bool operator!=(T& other)
    {
        return !(*this == other);
    }
    
    bool operator!=(const std::nullptr_t other) const
    {
        return !(*this == other);
    }
    
    operator bool() const
    {
        return mData != nullptr ? true : false;
    }
    
private:
    T* mData = nullptr;
    
};


template<class T>
class MyUniquePtr<T[]>
{
public:
    MyUniquePtr() = default;
    
    ~MyUniquePtr()
    {
        //delete[] mData;
    }
    
    MyUniquePtr(T*&& ptr) : mData(ptr)
    {
        ptr = nullptr;
        delete[] ptr;
    }
    
    MyUniquePtr(T& ptr) : mData(ptr)
    {
        mData = ptr.mData;
    }
    
    // move
    MyUniquePtr(T&& ptr) : mData(ptr.mData)
    {
        ptr = nullptr;
        delete[] ptr;
    }
    
    MyUniquePtr& operator=(T& other)
    {
        mData = other.mData;
    }

    T *get() const
    {
        return mData;
    }
    
    T *operator->() const
    {
        return mData;
    }
    
    T operator*() const
    {
        return *mData;
    }
 
    T& operator[](size_t index) const
    {
        return mData[index];
    }

    T& release()
    {
        //Releases the ownership of the managed object if any. get() returns nullptr after the call.
        auto tempData = mData;
        mData = nullptr;
        return *tempData;
    }

    void reset(T& ptr)
    {
        //oldPtr = mData; current_ptr = ptr; if(old_ptr != nullptr) get_deleter()(old_ptr)
        auto oldPtr = mData;
        mData = ptr;
        if (oldPtr != nullptr){
            delete[] oldPtr;
        }
    }
    
    void swap(const MyUniquePtr<T>& other)
    {
        std::swap(mData, other.mData);
    }
    
    bool operator==(T& other)
    {
        return this->get() == other.get();
    }
    
    
    bool operator==(const std::nullptr_t other) const
    {
        return mData == other;
    }
    
    bool operator!=(T& other)
    {
        return !(*this == other);
    }
    
    bool operator!=(const std::nullptr_t other) const
    {
        return !(*this == other);
    }

    operator bool() const
    {
        return mData != nullptr ? true : false;
    }
    
private:
    T* mData = nullptr;
    
    // TODO:
    //  typeof T
    //  make_unique()
    //  fix ~MyUniquePtr<T[]>: if delete[] malloc errors. if not, memory leaks when used in MyString.
    
    
    
};

