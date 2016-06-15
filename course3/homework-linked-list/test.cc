#include "linked_list.h"

#include <cassert>
#include <iostream>


int main()
{
    LinkedList<int> list;
    assert(list.empty());
    assert(list.begin() == list.end());

    list.push_front(1);
    assert(!list.empty());
    assert(list.size() == 1);
}