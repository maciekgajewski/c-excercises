#include "stack.h"
#include <assert.h>
#include <deque>
#include <list>
#include <vector>

template<typename T>
void assert_size(const T& container, std::size_t size) {
    assert(size == container.size());
    assert(!size == container.empty());
}

template<typename T>
void test() {
    T c;
    Complex complex1(1, 1);
    Complex complex2(2.0, 2.0);

    assert_size(c, 0);

    c.push_back(complex1);
    assert_size(c, 1);
    assert(Complex(1, 1) == c.back());
    assert(Complex(1, 1) == complex1);

    c.push_back(complex1);
    assert_size(c, 2);
    assert(Complex(1, 1) == c.back());
    assert(Complex(1, 1) == complex1);

    c.push_back(complex2);
    assert_size(c, 3);
    assert(Complex(2, 2) == c.back());
    assert(Complex(2, 2) == complex2);

    c.pop_back();
    assert_size(c, 2);
    assert(Complex(1, 1) == c.back());
    assert(Complex(1, 1) == complex1);

    Complex c1 = c.back();
    c.pop_back();
    assert_size(c, 1);
    assert(c1 == c.back());
    assert(c1 == complex1);

    c.pop_back();
    assert_size(c, 0);

    std::cout << "OK for " << typeid(T).name() << std::endl;
}

int main() {
    test<MyComplexLinkedList>();
    test<std::deque<Complex>>();
    test<std::list<Complex>>();
    test<std::vector<Complex>>();
}
