#include "linked_list.h"
#include <cassert>
#include <functional>


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
void test(const char* test_name, const execT& exp, const T& expected, bool should_succeed=true)
{
    if (should_succeed)
    {
        assert (exp() == expected);
    }
    else
    {
        TestResult outcome;
        try
        {
            exp();
            outcome = TestResult::FAIL;
        }
        catch(...)
        {
            outcome = TestResult::PASS;
        }
        assert (outcome == TestResult::PASS);
    }
    std::cout << "Passed: " << test_name << std::endl;
}

int main(int, char**)
{
    using namespace linked_list;
    using namespace std::literals;

    /* Basic tests for construction and assignment */
    LinkedList<int> empty_data;

    auto call_empty_front = std::bind(&LinkedList<int>::front, &empty_data);
    test("calling front on empty linked list raises error", call_empty_front, false, false);

    auto call_empty_size = std::bind(&LinkedList<int>::size, &empty_data);
    test("empty linked list has size 0", call_empty_size, 0);

    LinkedList<double> pi = 3.14159;
    auto call_front = std::bind(&LinkedList<double>::front, &pi);
    test("basic construction sets first value", call_front, 3.14159);

    auto call_size = std::bind(&LinkedList<double>::size, &pi);
    test("basic construction increments size", call_size, 1);

    /* Test push/pop front */
    pi.push_front(2.71828);
    call_front = std::bind(&LinkedList<double>::front, &pi);
    test("push front adds new item to list", call_front, 2.71828);
}
