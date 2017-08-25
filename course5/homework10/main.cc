#include "linked_list.h"
#include <cassert>
#include <functional>
#include <list>
#include <string>


/***
Please, write a singly-linked list, that behaves like a well-behaved container should.

The interface should include:

Default, copy and move constructor
Copy and move assignment operator
Constructor consuming pair of iterators.
begin(), end() (const and non-const)
push_front()  (copying and moving)
emplace_front()
pop_front()
front()
size()

Look at the interface of other std containers for detailed signatures and inspiration.
Cover the class with unit tests; don’t forget about corner cases.
Test your container with few std algorithms.
***/

struct Twosie
{
    Twosie() = default;
    Twosie(int one, int two)
    {
        mOne = one;
        mTwo = two;
    }
    int mOne = 0;
    int mTwo = 0;
};

std::ostream& operator<<(std::ostream& s, const Twosie& t)
{
    s << "(" << t.mOne << "-|-" << t.mTwo << ")";
    return s;
}
bool operator==(const Twosie& t1, const Twosie& t2)
{
    return (t1.mOne == t2.mOne && t1.mTwo == t2.mTwo);
}

enum TestResult { PASS, FAIL };
template<typename execT, typename T>
void test(std::string test_name, const execT& exp, const T& expected)
{
    auto res = exp();
    bool result_eq_expected = res == expected;

    if (result_eq_expected)
        std::cout << "------> Passed: " << test_name << std::endl;
    else
        std::cout << "------> Failed: " << test_name << std::endl;
}

template<typename T>
void test(std::string test_name, const T& exp, const T& expected)
{
    bool result_eq_expected = exp == expected;

    if (result_eq_expected)
        std::cout << "------> Passed: " << test_name << std::endl;
    else
        std::cout << "------> Failed: " << test_name << std::endl;
}

int main(int, char**)
{
    using namespace linked_list;
    using namespace std::literals;

    /* Basic tests for construction and assignment */
    LinkedList<int> empty_data;

    auto call_empty_front = std::bind(&LinkedList<int>::front, &empty_data);
    // test_fails("calling front on empty linked list raises error", call_empty_front);

    auto call_empty_size = std::bind(&LinkedList<int>::size, &empty_data);
    test("empty linked list has size 0", call_empty_size, 0);

    empty_data.push_front(3);
    test("push_front on empty linked list sets first value", call_empty_front, 3);

    LinkedList<double> pi = 3.14159;
    auto call_front = std::bind(&LinkedList<double>::front, &pi);
    test("basic construction sets first value", call_front, 3.14159);

    auto call_size = std::bind(&LinkedList<double>::size, &pi);
    test("basic construction increments size", call_size, 1);

    /* Test push/pop front */
    std::list<double> doubles = {2.71828, 1.1, 2.2, 3.3};
    int size = 1;
    for (auto el : doubles)
    {
        pi.push_front(el);
        size++;
        test("push front adds new item to list: " + std::to_string(el), call_front, el);
        test("push front increments size: " + std::to_string(size), call_size, size);
    }
    pi.print();

    pi.push_front(3.14);
    size++;
    doubles.reverse();

    for (auto el : doubles)
    {
        pi.pop_front();
        size--;
        pi.print();
        test("pop front removes one item from list: " + std::to_string(call_front()), call_front, el);
        test("push front decrements size: " + std::to_string(size), call_size, size);
    }

    /* Test emplace front */
    Twosie some_struct(3, 5);
    LinkedList<Twosie> emplace_tester;
    auto emplace_tester_front = std::bind(&LinkedList<Twosie>::front, &emplace_tester);
    auto emplace_tester_size = std::bind(&LinkedList<Twosie>::size, &emplace_tester);

    std::list<int> ints = {3, 7, 4, 5};
    size = 0;
    for (auto el : ints)
    {
        emplace_tester.emplace_front(el, 5);
        size++;
        test("emplace front adds new item to list: " + std::to_string(el), emplace_tester_front, Twosie(el, 5));
        test("emplace front increments size: " + std::to_string(size), emplace_tester_size, size);
    }

    /* Test equality */
    // LinkedList<int> also_empty;
    // test("empty linked list equality", also_empty, empty_data);

    /* Test iterators */
    std::cout << *pi.begin() << std::endl;
    test("begin iterator returns pointer to first item in list", *pi.begin(), pi.front());
    pi.print();

    for (auto el : doubles)
    {
        pi.push_front(el);
        test("begin iterator returns pointer to first item in list after incrementing", *pi.begin(), pi.front());
    }
    pi.print();

    doubles.reverse();
    auto it = pi.begin();
    for (auto el : doubles)
    {
        test("begin iterator can be incremented: " + std::to_string(el), *it, el);
        ++it;
    }

    // for (auto el : pi)
    // {
    //     test("iteration over entire list works: " + std::to_string(el), el, el);
    // }
}
