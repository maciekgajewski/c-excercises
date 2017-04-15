#pragma once
#include <iostream>
#include <memory>
#include <stdexcept>

namespace linked_list
{

template<class T, class Allocator = std::allocator<T>>
struct Node
{
    std::unique_ptr<T> data;
    std::unique_ptr<Node> next;
};

template<class T, class Allocator = std::allocator<T>>
class LinkedList
{
public:
    // Basic assignment constructors
    LinkedList() = default;
    LinkedList(T src_data)
    {
        head.data = std::make_unique<T>(val);
        mSize += 1;
    }

    int size() { return mSize; }
    T front()
    {
        if (mSize > 0)
            return *head.data.get();
        throw std::range_error("Calling front on empty LinkedList is undefined.");
    }

private:
    Node<T> head;
    int mSize = 0;

}; // LinkedList
} // namespace
