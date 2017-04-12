#include "linked_list.h"
#include <cassert>

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

int main(int, char**)
{
    using namespace linked_list;
    using namespace std::literals;

    /* Basic tests for construction and assignment */
    LinkedList<int> empty_data;
    assert (empty_data.size() == 1);

    LinkedList<double> pi = 3.14159;
    assert (pi.front() == 3.14159);
    assert (pi.size() == 1);
}
