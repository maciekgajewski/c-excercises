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
    // Basic assignment constructors
    LinkedList() = default;
    LinkedList(const T& val) // TODO T&& val ?
    {
        std::cout << "Basic construction: from " << val << std::endl;
        data = std::make_unique<T>(val);
        mSize += 1;
    }
    // Copy construction
    LinkedList(const LinkedList& src)
    {
        std::cout << "Copy construction: from " << src.front() << std::endl;
        data = std::make_unique<T>(src.front());
        if (src.next)
            next = std::make_unique<LinkedList<T>>(*src.next.get());
        mSize = src.mSize;
    }
    // Move construction
    LinkedList(LinkedList&& src)
    {
        std::cout << "Move construction: from " << src.front() << std::endl;
        data = std::move(src.data);
        next = std::move(src.next);
        mSize = src.mSize;
    }
    // Copy assignment
    LinkedList& operator=(const LinkedList& src)
    {
        std::cout << "Copy assignment: from " << src.front() << std::endl;
        data = std::make_unique<T>(src.front());
        if (src.next)
            next = std::make_unique<LinkedList<T>>(*src.next.get());
        mSize = src.mSize;
        return *this;
    }
    // Move assignment
    LinkedList& operator=(LinkedList&& src)
    {
        std::cout << "Move assignment: from " << src.front() << std::endl;
        data = std::move(src.data);
        next = std::move(src.next);
        mSize = src.mSize;
        return *this;
    }

    int size() { return mSize; }
    T front() const // TODO should this be a pointer? const?
    {
        if (data)
            return *data.get();
        throw std::range_error("Calling front on empty LinkedList is undefined.");
    }
    void push_front(const T& val)
    {
        std::cout << "pushing front" << std::endl;
        if (mSize > 0)
        {
            LinkedList<T> new_node;
            new_node.data = std::move(this->data);
            new_node.next = std::move(this->next);
            data = std::make_unique<T>(val);
            next = std::make_unique<LinkedList<T>>(std::move(new_node));
        }
        else
        {
            data = std::make_unique<T>(val);
        }
        mSize++;
    }

    template< class... Args >
    void emplace_front(Args&&... args)
    {
        if (mSize > 0)
        {
            LinkedList<T> new_node;
            new_node.data = std::move(this->data);
            new_node.next = std::move(this->next);
            data = std::make_unique<T>(args...);
            next = std::make_unique<LinkedList<T>>(std::move(new_node));
        }
        else
        {
            data = std::make_unique<T>(args...);
        }
        mSize++;
    }

    void pop_front()
    {
        if (next)
        {
            LinkedList<T> new_head = std::move(*next.get());
            data = std::move(new_head.data);
            next = std::move(new_head.next);
            mSize--;
        }
    }

    void print() const
    {
        LinkedList<T> current = *this;
        for (auto i = 0; i < mSize; i++)
        {
            std::cout << i << " [" << current.front() << "]" << std::endl;
            current = *(current.next.get());
        }
        std::cout << std::endl;
    }

private:
    std::unique_ptr<T> data;
    std::unique_ptr<LinkedList<T>> next;
    int mSize = 0;

}; // LinkedList
} // namespace
