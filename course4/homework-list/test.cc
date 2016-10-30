#include <iostream>
#include "list.hh"
#include <cassert>
#include <algorithm>

int main()
{
    course::List<std::string> x;

    // push/pop tests
    x.push_front("ABC");
    x.push_front("XYZ");
    assert(x.size() == 2);
    assert(x.pop_front() == "XYZ");
    assert(x.size() == 1);
    x.push_front("OOO");
    assert(x.front() == "OOO");
    assert(x.size() == 2);

    //clean test
    x.empty();
    assert(x.size() == 0);
    //usable after clean
    x.push_front("XYZ");
    assert(x.size() == 1);

    course::List<int> y;
    y.push_front(2);
    y.push_front(3);
    y.push_front(2);
    y.push_front(1);
    y.push_front(2);

    int count = std::count<course::ListIterator<int>, int>(y.begin(), y.end(), 3);
}
