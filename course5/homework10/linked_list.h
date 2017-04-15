#pragma once
#include <iostream>
#include <memory>
#include <stdexcept>

namespace linked_list
{

template<class T, class Allocator = std::allocator<T>>
class LinkedList
{
public:
    LinkedList() = default;
    LinkedList(T src_data)
    {
        data = std::make_unique<T>(src_data);
        mSize += 1;
    }

    int size() { return mSize; }
    T front()
    {
        if (data)
            return *data.get();
        throw std::range_error("Calling front on empty LinkedList is undefined.");
    }

private:
    std::unique_ptr<T> data;
    std::unique_ptr<LinkedList> next;
    int mSize = 0;

}; // LinkedList
} // namespace
