#include "complex_stack.hh"

#include <iostream>
#include <assert.h>
#include <stack>
#include <list>
#include <vector>
#include <deque>

template<typename T> void single_element_test()
{
    std::stack<Complex, T> stack;
    assert(stack.empty());
    Complex c(1.1);
    stack.push(c);
    assert(stack.top() == c);
    assert(stack.size() == 1);
    stack.pop();
    assert(stack.size() == 0);
    assert(stack.empty());
}

template<typename T> void multiple_elements_test()
{
    std::stack<Complex, T> stack;
    for (int i = 1; i < 8; i++)
    {
        stack.push(Complex(i, -i));
        assert(stack.size() == i);
    }
    assert(stack.top() == Complex(7, -7));
    stack.pop();
    assert(stack.top() == Complex(6, -6));
    assert(stack.size() == 6);

    stack.push(Complex(7, -7));

    for (int i = 7; i > 0; i--)
    {
        assert(stack.top() == Complex(i, -i));
        assert(stack.size() == i);
        stack.pop();
    }
    assert(stack.empty());
    assert(stack.size() == 0);
}

template<typename T> void test()
{
    single_element_test<T>();
    multiple_elements_test<T>();
}

void run_tests()
{
   test<ComplexStack>();
   test<std::vector<Complex>>();
   test<std::list<Complex>>();
   test<std::deque<Complex>>();
}

int main(int argc, char** argv)
{
    run_tests();
};
