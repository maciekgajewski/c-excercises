#include <cassert>
#include <iostream>
#include <list>

#include "linkedlist.h"

template<typename ListType>
void ListTest() {

    ListType testList;
    assert(testList.empty());
    assert(testList.size() == 0);

    testList.push_front(123);
    assert(!testList.empty());
    assert(testList.size() == 1);

    testList.push_front(124);
    assert(testList.size() == 2);

    testList.push_front(125);
    assert(testList.size() == 3);

    testList.pop_front();
    assert(testList.size() == 2);

    testList.pop_front();
    assert(testList.size() == 1);

    testList.pop_front();
    assert(testList.empty());
    assert(testList.size() == 0);


}

int main() {
    std::cout << "list" << std::endl; 

    std::cout << "testing std::list" << std::endl;
    ListTest<std::list<int>>();

    std::cout << "testing mau::list" << std::endl;
    ListTest<mau::list<int>>();

    return 0;
}
