#include "unique_ptr.h"
#include "unique_ptr.cc"

#include <cassert>
#include <iostream>
#include <memory>


template<typename UniquePtrType>
void unique_ptr_int_test()
{
	// default contructor
	UniquePtrType ptr;
	assert(ptr.get() == nullptr);
	assert(!ptr);
	
	// reset
	UniquePtrType ptr2;
	ptr2.reset(new int(42));
	assert(ptr2);
	assert(*ptr2.get() == 42);
	
	// release
	int* i = ptr.release();
	assert(i == nullptr);
	assert(!ptr);
	int* i2 = ptr2.release();
	assert(*i2 == 42);
	assert(!ptr2);
	
	// swap
	ptr.reset(i2);
	ptr2.reset(i);
	ptr.swap(ptr2);
	assert(!ptr);
	assert(!ptr.get());
	assert(*ptr2.get() == 42);
	
}

int main()
{
	// test fior std::unique_ptr
	std::cout << "Testing std::unique_ptr..." << std::endl;
	unique_ptr_int_test<std::unique_ptr<int>>();
	std::cout << "std::unique_ptr test passes" << std::endl;
	
	// test for karun::unique_ptr
	std::cout << "Testing karun::unique_ptr..." << std::endl;
	unique_ptr_int_test<karun::unique_ptr<int>>();
	std::cout << "karun::unique_ptr test passes" << std::endl;
}