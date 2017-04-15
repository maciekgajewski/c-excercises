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

    // Node(Node& src) // copy construction
    // {
    //     std::cout << "Node copy construction: " << *src.data.get() << std::endl;
    //     data = std::make_unique<T>(*src.data.get());
    //     next = src.next;
    // }
    Node(Node&& src) // move construction
    {
        std::cout << "Node move construction: " << *src.data.get() << std::endl;
        data = std::move(src.data);
        next = src.next;
    }

    // Node& operator=(Node& src) // copy assignment
    // {
    //     std::cout << "Node copy assignment: " << *src.data.get() << std::endl;
    //     data = std::make_unique<T>(*src.data.get());
    //     next = src.next;
    //     return *this;
    // }

    Node& operator=(Node&& src) // move assignment
    {
        std::cout << "Node move assignment: " << src.getData() << std::endl;
        data = std::move(src.data);
        next = src.next;
        return *this;
    }

    T getData()
    {
        return *data.get();
    }

    std::unique_ptr<T> data;
    std::unique_ptr<Node<T>> next;
};

template<class T, class Allocator = std::allocator<T>>
class LinkedList
{
public:
    // Basic assignment constructors
    LinkedList() = default;
    LinkedList(const T& val) // TODO T&& val ?
    {
        head = Node<T>(val);
        mSize += 1;
    }
    // Copy/Move construction
    LinkedList(const LinkedList& src)
    {
        std::cout << "Copy construction" << std::endl;
        mSize = src.mSize;
    }
    LinkedList(LinkedList&& src)
    {
        std::cout << "Move construction" << std::endl;
        mSize = src.mSize;
    }
    // Copy/Move assignment
    LinkedList& operator=(const LinkedList& src)
    {
        std::cout << "Copy assignment" << std::endl;
        mSize = src.mSize;
        return *this;
    }
    LinkedList& operator=(LinkedList&& src)
    {
        std::cout << "Move assignment" << std::endl;
        mSize = src.mSize;
        return *this;
    }

    int size() { return mSize; }
    T front() // TODO should this be a pointer? const?
    {
        if (mSize > 0)
            return head.getData();
        throw std::range_error("Calling front on empty LinkedList is undefined.");
    }
    void push_front(const T& val)
    {
        std::cout << "Push front -- new front: " << val << std::endl;
        std::cout << "Push front -- current head data: " << head.getData() << std::endl;
        Node<T> old_head = std::move(head);
        head = Node<T>(val, old_head);


        // head = Node<T>(val, head);
        std::cout << "Push front -- new head data: " << head.getData() << std::endl;
        std::cout << "Push front -- next data: " << head.next->getData() << std::endl;
        mSize += 1;
    }
    void pop_front()
    {
        std::cout << "Pop front -- current head data: " << head.getData() << std::endl;
        std::cout << "Pop front -- next data: " << head.next->getData() << std::endl;
        if (mSize > 0)
        {
            head = std::move(*head.next);
        }
    }

    // void print_list()
    // {
    //     Node<T> current = head;
    //     for (auto i = 0; i < mSize; i++)
    //     {
    //         std::cout << '[' << current.getData() << '|' << current.next << ']';
    //         current = *(head.next);
    //     }
    //     std::cout << std::endl;
    // }

private:
    Node<T> head;
    int mSize = 0;

}; // LinkedList
} // namespace
