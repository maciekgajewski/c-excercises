#include "llist.h"
#include <assert.h>
#include <algorithm>
#include <iostream>

void square(int& n) 
{
        n = n * n; 
}

int main(int, char**)
{
    course::llist<int> list;
    list.push_front(2);
    list.push_front(3);
    list.push_front(5);
    assert( list.size() == 3 );
    assert( list.front() == 5 );
    course::llist<int> list2 = list;

    list2.push_front(7);
    list.pop_front();
    assert( list.size() == 2 );
    assert( list2.size() == 4 );
    assert( list.front() == 3 );
    list.pop_front();
    assert( list.size() == 1 );
    assert( list.front() == 2 );
    list.pop_front();
    assert( list.size() == 0 );
    course::llist<int> list3;
    list3.push_front(12);
    list3 = list2;
    assert( list3.size() == 4);

    auto it1 = list3.begin();
    auto it2 = list3.begin();
    ++it2;
    ++it2;
    course::llist<int> list4(it1, it2);
    assert( list4.size() == 2 );
    assert( list4.front() == list3.front() );

    std::fill(it1, it2, 42);
    assert( list3.front() == 42 );
    list3.pop_front();
    assert( list3.front() == 42 );

    auto list5 = list3;
    std::for_each(list3.begin(), list3.end(), square);
    assert( list3.front() == list5.front() * list5.front() );
    list3.pop_front();
    list5.pop_front();
    assert( list3.front() == list5.front() * list5.front() );
    list3.pop_front();
    list5.pop_front();
    assert( list3.front() == list5.front() * list5.front() );
}