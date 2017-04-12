#pragma once
#include <iostream>
#include <memory>

namespace linked_list
{

template<class T, class Allocator = std::allocator<T>>
class LinkedList
{
public:
    LinkedList() = default;

    // int size();

private:
    T * data = nullptr;
    T * next = nullptr;
    int msize = 0;

}; // LinkedList

template class LinkedList<int>;

} // namespace
