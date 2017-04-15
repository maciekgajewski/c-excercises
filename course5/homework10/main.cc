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

enum TestResult { PASS, FAIL };
template<typename execT, typename T>
void test(std::string test_name, const execT& exp, const T& expected)
// void test(const char* test_name, const execT& exp, const T& expected, bool should_succeed=true)
{
    auto res = exp();
    std::cout << res << std::endl;
    bool result_eq_expected = res == expected;
    // if (should_succeed)
    // {
        // auto res = exp();
        // assert (res == expected);
    // }
    // else
    // {
    //     TestResult outcome;
    //     try
    //     {
    //         exp();
    //         outcome = TestResult::FAIL;
    //     }
    //     catch(...)
    //     {
    //         outcome = TestResult::PASS;
    //     }
    //     assert (outcome == TestResult::PASS);
    // }
    if (result_eq_expected)
        std::cout << "Passed: " << test_name << std::endl;
    else
        std::cout << "Failed: " << test_name << std::endl;
}

int main(int, char**)
{
    using namespace linked_list;
    using namespace std::literals;

    /* Basic tests for construction and assignment */
    LinkedList<int> empty_data;

    // auto call_empty_front = std::bind(&LinkedList<int>::front, &empty_data);
    // test("calling front on empty linked list raises error", call_empty_front, false, false);

    auto call_empty_size = std::bind(&LinkedList<int>::size, &empty_data);
    test("empty linked list has size 0", call_empty_size, 0);

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
        // pi.print_list();
        test("push front adds new item to list: " + std::to_string(el), call_front, el);
        test("push front increments size", call_size, size);
        size++;

    }
    pi.push_front(3.14);
    doubles.reverse();

    std::cout << "------------------" << std::endl;

    for (auto el : doubles)
    {
        pi.pop_front();
        test("pop front removes one item from list: " + std::to_string(call_front()), call_front, el);
    }

}
