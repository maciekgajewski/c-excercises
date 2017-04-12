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
    LinkedList(T src_data){ data = &src_data; }

    int size() { return msize; }
    T front() { return *data; }

private:
    T * data = nullptr;
    T * next = nullptr;
    int msize = 1;

}; // LinkedList

template class LinkedList<int>;
template class LinkedList<double>;

} // namespace
