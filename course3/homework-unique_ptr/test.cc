#include "unique_ptr.h"
#include "unique_ptr.cc"

#include <cassert>
#include <iostream>
#include <memory>


template<template<class...> class UniquePtrType>
void unique_ptr_test()
{
	// default contructor
	UniquePtrType<int> ptr;
	assert(!ptr);
	assert(ptr.get() == nullptr);
	
	// initialization constructor
	UniquePtrType<int> ptr2(nullptr);
	assert(!ptr2);
	
	int* i = new int(42);
	UniquePtrType<int> ptr3(i);
	assert(ptr3);
	assert(*ptr3.get() == 42);
	
	// move constructor
	UniquePtrType<int> ptr4 = std::move(ptr3);
	assert(*ptr4.get() == 42);
	assert(ptr4.get() == i);
	
	// move assignment operator
	ptr3 = std::move(ptr4);
	assert(*ptr3.get() == 42);
	assert(ptr3.get() == i);
	
	// nullptr assignment operator
	ptr3 = nullptr;
	assert(!ptr3);
	
	// reset
	ptr.reset(new int(42));
	assert(*ptr.get() == 42);
	
	ptr.reset();
	assert(!ptr);
	
	ptr.reset(new int(42));
	ptr.reset(nullptr);
	assert(!ptr);
	
	// release
	ptr.reset(new int(42));
	i = ptr.release();
	assert(*i == 42);
	
	ptr.reset(i);
	assert(*ptr.get() == 42);
	
	ptr.reset();
	i = ptr.release();
	assert(i == nullptr);
	
	// swap
	ptr2.reset(new int(42));
	ptr.swap(ptr2);
	assert(!ptr2);
	assert(*ptr.get() == 42);
	
	// operator*
	struct S { int i = 42; };
	UniquePtrType<S> ptr5(new S);
	S s = *ptr5;
	assert(s.i == 42);
	
	// operator->
	assert(ptr5->i == 42);
	
}

int main()
{
	// test fior std::unique_ptr
	std::cout << "Testing std::unique_ptr..." << std::endl;
	unique_ptr_test<std::unique_ptr>();
	std::cout << "std::unique_ptr test passes" << std::endl;
	
	// test for karun::unique_ptr
	std::cout << "Testing karun::unique_ptr..." << std::endl;
	unique_ptr_test<karun::unique_ptr>();
	std::cout << "karun::unique_ptr test passes" << std::endl;
}