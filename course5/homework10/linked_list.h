#pragma once
#include <iostream>
#include <memory>
#include <stdexcept>

namespace linked_list
{

template<class T, class Allocator = std::allocator<T>>
struct Node
{
    Node() = default;
    Node(const T& val) // TODO T&& val ?
    {
        data = std::make_unique<T>(val);
    }
    Node(const T& val, Node& next_node) // TODO T&& val ?
    {
        data = std::make_unique<T>(val);
        next = &next_node;
    }

    T getData()
    {
        return *data.get();
    }

    std::unique_ptr<T> data;
    Node* next = nullptr;
};

template<class T, class Allocator = std::allocator<T>>
class LinkedList
{
public:
    // Basic assignment constructors
    LinkedList() = default;
    LinkedList(T src_data)
    {
        head = Node<T>(val);
        mSize += 1;
    }

    int size() { return mSize; }
    T front()
    {
        if (mSize > 0)
            return head.getData();
        throw std::range_error("Calling front on empty LinkedList is undefined.");
    }
    void push_front(const T& val)
    {
        head = Node<T>(val, head);
        mSize += 1;
    }
    // void pop_front()
    // {
    //     if (next)
    //     {
    //         data = next;
    //     }
    //         return *data.get();
    //     throw std::range_error("Calling front on empty LinkedList is undefined.");
    // }

private:
    Node<T> head;
    int mSize = 0;

}; // LinkedList
} // namespace
