#include <iostream>
/*
re-implemention of http://en.cppreference.com/w/cpp/memory/unique_ptr
*/

template<class T>
class MyUniquePtr
{
public:
    MyUniquePtr(){
        //std::cout/g << "default constructor this= " << this << std::endl;
    }
    
    MyUniquePtr(std::nullptr_t){
        //std::cout/g << "MyUniquePtr(std::nullptr_t)this= " << this << std::endl;
    }
    
    MyUniquePtr(T ptr) : mData(ptr){
        //std::cout/g << "MyUniquePtr(T ptr) this= " << this << std::endl;
        ptr = nullptr;
    }
    
    explicit MyUniquePtr(T* ptr) : mData(ptr){
        //std::cout/g << "MyUniquePtr(T* ptr) this= " << this << std::endl;
        ptr = nullptr;
        
    }
    
    explicit MyUniquePtr(T& ptr) : mData(ptr){
        //std::cout/g << "MyUniquePtr(T& ptr)  this= " << this << std::endl;
        ptr = nullptr;
    }
    
    MyUniquePtr(MyUniquePtr&& ptr)
    {
        //std::cout/g << "MyUniquePtr(T&& ptr)  this= " << this << std::endl;
        mData = ptr.mData;
        ptr.mData = nullptr;
    }
    
    ~MyUniquePtr()
    {
        //std::cout/g << "\n~this= " << this << std::endl;
        delete mData;
    }
    
    MyUniquePtr& operator=(MyUniquePtr&& other)
    {
        //std::cout/g << "operator=(T& other) this= " << this << std::endl;
        std::swap(mData,other.mData);
        return *this;
    }

    T* get() const
    {
        return mData;
    }

    
    T* operator->() const
    {
        return mData;
    }
    
    T operator*() const
    {
        return *mData;
    }

    T* release()
    {
        //Releases the ownership of the managed object if any. get() returns nullptr after the call.
        auto retPtr = mData;
        mData = nullptr;
        return retPtr;
    }
    
    void reset(T& ptr)
    {
        //oldPtr = mData; current_ptr = ptr; if(old_ptr != nullptr) get_deleter()(old_ptr)
        auto* oldPtr = mData;
        mData = ptr;
        delete oldPtr;
    }

    void reset()
    {
        if (mData){
            delete mData;
        }
    }
    
    void swap(MyUniquePtr<T>& other)
    {
        std::swap(mData,other.mData);
    }

    bool operator==(MyUniquePtr& other) const
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
        return mData != nullptr;
    }
    
private:
    T* mData = nullptr;
    
};


template<class T>
class MyUniquePtr<T[]>
{
public:
    MyUniquePtr(){
        //std::cout/g << "default constructor this= " << this << std::endl;
    }
    
    MyUniquePtr(std::nullptr_t){
        //std::cout/g << "MyUniquePtr(std::nullptr_t)this= " << this << std::endl;
    }
    
    MyUniquePtr(T ptr) : mData(ptr){
        //std::cout/g << "MyUniquePtr(T ptr) this= " << this << std::endl;
        ptr = nullptr;
    }
    
    explicit MyUniquePtr(T* ptr) : mData(ptr){
        //std::cout/g << "MyUniquePtr(T* ptr) this= " << this << std::endl;
        ptr = nullptr;
        
    }
    
    MyUniquePtr(T& ptr) : mData(ptr){
        //std::cout/g << "MyUniquePtr(T& ptr)  this= " << this << std::endl;
        ptr = nullptr;
    }
    
    MyUniquePtr(MyUniquePtr&& ptr)
    {
        //std::cout/g << "MyUniquePtr(T& ptr)  this= " << this << std::endl;
        mData = ptr.mData;
        ptr.mData = nullptr;
    }
    
    ~MyUniquePtr()
    {
        ////std::cout/g << "\n~this= " << this << std::endl;
        delete[] mData;
    }
    
    MyUniquePtr& operator=(MyUniquePtr&& other)
    {
        //std::cout/g << "operator=(T& other) this= " << this << std::endl;
        std::swap(mData,other.mData);
        return *this;
    }

    T* get() const
    {
        return mData;
    }

    
    T* operator->() const
    {
        return mData;
    }
    
    T operator*() const
    {
        return *mData;
    }

    T* release()
    {
        //Releases the ownership of the managed object back to caller. get() returns nullptr after the call.
        auto* retPtr = mData;
        mData = nullptr;
        return retPtr;
    }
    
    void reset(T& ptr)
    {
        //oldPtr = mData; current_ptr = ptr; if(old_ptr != nullptr) get_deleter()(old_ptr)
        auto oldPtr = mData;
        mData = ptr;
        delete[] oldPtr;
    }

    void reset()
    {
        delete[] mData;
    }
    
    void swap(MyUniquePtr<T>& other)
    {
        std::swap(mData,other.mData);
    }

    bool operator==(MyUniquePtr& other) const
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
        return mData != nullptr;
    }

    T& operator[](size_t index) const
    {
        return mData[index];
    }
    
private:
    T* mData = nullptr;
    
};




