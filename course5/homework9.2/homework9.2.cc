#include <cassert>
#include <string>
#include "unique_ptr.h"

template <typename T>
void test(T const & value)
{
	jds::unique_ptr<T> p1 = jds::make_unique<T>(value);
	assert (*p1 == value);
	T * ptr_before_move = p1.get();
	jds::unique_ptr<T> p2 = std::move(p1);
	assert(*p2 == value);
	assert(ptr_before_move == p2.get());
	assert(p1.get() == nullptr);
}

int main()
{
	test(9);
	test(std::string("Hello world"));
}
