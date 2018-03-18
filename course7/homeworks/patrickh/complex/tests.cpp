#include <vector>
#include <deque>
#include <list>
#include <stack>
#include <assert.h>
#include <iostream>
#include "complex_linked_list.h"

template<typename T>
void test()
{
    std::stack<Complex, T> stack;
    assert(stack.empty());

    Complex complex1(1,3);
    stack.push(complex1);

    assert(!stack.empty());
    assert(stack.top() == complex1);
    assert(stack.size() == 1);

    Complex complex2(-6,-1);
    stack.push(complex2);

    assert(stack.top() == complex2);
    assert(!stack.empty());
    assert(stack.size() == 2);

    stack.pop();

    assert(stack.top() == complex1);
    assert(!stack.empty());
    assert(stack.size() == 1);

    stack.pop();
    assert(stack.empty());
    assert(stack.size() == 0);
}

int main(int argc, char** argv)
{
    test<ComplexLinkedList>();
    test<std::vector<Complex>>();
    test<std::list<Complex>>();
    test<std::deque<Complex>>();
};