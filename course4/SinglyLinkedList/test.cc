#include "sllist.hh"
#include "sll_iterator.hh"

#include <cassert>
#include <sstream>
#include <iostream>
#include <forward_list>
#include <algorithm>

template<typename ListType>
void test()
{
    ListType list;
    assert(list.empty());

    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    list.push_front(3);
    list.push_front(7);
    list.push_front(8);
    list.push_front(9);

    assert(list.front() == 9);

    list.pop_front();
    assert(list.front() == 8);

    auto numOf3s = std::count(list.begin(), list.end(), 3);
    assert(numOf3s== 2);

    auto result = std::find_if(list.begin(), list.end(), [](int i){return i > 5;});
    assert(result != list.end());

    auto result2 = std::find_if(list.begin(), list.end(), [](int i){return i > 10;});
    assert(result2 == list.end());

}

int main()
{
    std::cout << "Testing std::forward_list..." << std::endl;
    test<std::forward_list<int>>();
    std::cout << "std::forward passes" << std::endl;

    std::cout << "Testing course::sllist..." << std::endl;
    test<course::sllist<int>>();
    std::cout << "course::sllist passes" << std::endl;
	
}
