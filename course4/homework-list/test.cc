#include <iostream>
#include "list.hh"
#include <cassert>
#include <algorithm>
#include<forward_list>

template<typename T>
void RunStringTest()
{
    T list;
    list.push_front("ABC");
    assert(!list.empty());
    list.push_front("XYZ");
    assert(list.front() == "XYZ");
    list.pop_front();
    assert(list.front() == "ABC");
    list.pop_front();
    assert(list.empty());
    list.push_front("OOO");
    assert(list.front() == "OOO");
    list.push_front("XYZ");
    assert(list.front() == "XYZ");
}

template<typename T>
void RunAlgoTest()
{
    T list;
    list.push_front(2);
    list.push_front(3);
    list.push_front(2);
    list.push_front(1);
    list.push_front(2);

    int count = std::count_if(list.begin(), list.end(), [](int x) {return x == 2;});
    assert(count == 3);
}

int main()
{
    RunStringTest<course::List<std::string>>();
    RunStringTest<std::forward_list<std::string>>();

    RunAlgoTest<course::List<int>>();
    RunAlgoTest<std::forward_list<int>>();
    std::cout << "DONE" << std::endl;
}
