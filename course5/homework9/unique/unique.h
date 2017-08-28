#pragma once

namespace course
{

template <class T>
class unique_ptr 
{
    public:
            unique_ptr() : ptr( nullptr ) {}
            unique_ptr(T* init_ptr ) : ptr(init_ptr) {}
            ~unique_ptr() { delete ptr; }
            unique_ptr(const unique_ptr&) = delete;
            unique_ptr& operator=( const unique_ptr& ) = delete;
            unique_ptr( unique_ptr&& other)
            {
                this->ptr = other.ptr;
                other.ptr = nullptr;
            }
            unique_ptr& operator=( unique_ptr&& other )
            {
                delete this->ptr;
                this->ptr = other.ptr;
                other.ptr = nullptr;
                return *this;
            }
            T* get() { return ptr; }
    private:
            T* ptr;

};

template <typename T>
unique_ptr<T> make_unique()
{
    unique_ptr<T> p( new T );
    return p;
}

}