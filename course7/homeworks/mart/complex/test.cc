#include "complex_linked_list.hh"
#include <assert.h>
#include <stack>
#include <list>
#include <vector>
#include <deque>

template<typename CollectionType>
void assert_empty(std::stack<Complex, CollectionType>& c)
{
	assert(c.empty());
	assert(c.size() == 0);
}

template<typename CollectionType>
void assert_state(std::stack<Complex, CollectionType>& c, std::size_t expectedSize, const Complex& topElement)
{
	assert(!c.empty());
	assert(c.size() == expectedSize);
	assert(c.top() == topElement);
}

template<typename CollectionType>
void test()
{
	std::stack<Complex, CollectionType> c;
	Complex c1(12.34, 56.78);
	Complex c2(13.37);
	Complex c3(42.42, 42.0);

	assert_empty(c);
	c.push(c1);
	assert_state(c, 1, c1);
	c.pop();
	assert_empty(c);

	c.push(c1);
	assert_state(c, 1, c1);
	c.push(c2);
	assert_state(c, 2, c2);
	c.push(c3);
	assert_state(c, 3, c3);
	c.pop();
	assert_state(c, 2, c2);
	c.pop();
	assert_state(c, 1, c1);
	c.pop();
	assert_empty(c);
}

int main(/*int argc, char** argv*/)
{
	test<ComplexLinkedList>();
	test<std::vector<Complex>>();
	test<std::list<Complex>>();
	test<std::deque<Complex>>();
}
