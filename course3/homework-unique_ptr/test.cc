#include "unique_ptr.h"

#include <cassert>
#include <iostream>
#include <memory>


struct Number
{
	int n;
	static int ctr;
	Number(int n) : n(n) { ctr++; }
	Number(const Number& n) : n(n.n) { ctr++; }
	~Number() { ctr--; }
};
int Number::ctr = 0;

template<typename UniquePtr, UniquePtr (*MakeUnique)(int&&)>
void unique_ptr_test()
{
	// default contructor
	UniquePtr u1;
	assert(u1.get() == nullptr);
	assert(!u1);
	
	// initialization constructor
	UniquePtr u2(nullptr);
	assert(!u2);
	assert(Number::ctr == 0);
	
	Number* n_ptr = new Number(42);
	UniquePtr u3(n_ptr);
	assert(u3);
	assert((*u3.get()).n == 42);
	assert(Number::ctr == 1);
	
	// operator* and operator->
	assert((*u3).n == 42);
	assert(u3->n == 42);
	
	// operator== and operator!=
	assert(u1 == u2);
	assert(u2 != u3);
	assert(u3 != UniquePtr(new Number(42)));
	assert(Number::ctr == 1);
	
	// move constructor
	UniquePtr u4 = std::move(u3);
	assert(u4->n == 42);
	assert(u4.get() == n_ptr);
	assert(!u3);
	assert(Number::ctr == 1);
	
	// move assignment operator
	UniquePtr u5(new Number(u4->n * 10));
	assert(u5->n == 420);
	assert(Number::ctr == 2);
	u5 = std::move(u4);
	assert(u5->n == 42);
	assert(u5.get() == n_ptr);
	assert(!u4);
	assert(Number::ctr == 1);
	
	// nullptr assignment operator
	u5 = nullptr;
	assert(u5.get() == nullptr);
	assert(!u5);
	assert(Number::ctr == 0);
	
	// reset
	u1.reset(new Number(42));
	assert(u1->n == 42);
	assert(Number::ctr == 1);
	
	u1.reset();
	assert(!u1);
	assert(Number::ctr == 0);
	
	u1.reset(new Number(42));
	u1.reset(nullptr);
	assert(!u1);
	assert(Number::ctr == 0);
	
	// release
	u1.reset(new Number(42));
	n_ptr = u1.release();
	assert(n_ptr->n == 42);
	assert(!u1);
	assert(Number::ctr == 1);
	
	u1.reset(n_ptr);
	assert(u1->n == 42);
	assert(Number::ctr == 1);
	
	u1.reset();
	n_ptr = u1.release();
	assert(n_ptr == nullptr);
	assert(!u1);
	assert(Number::ctr == 0);
	
	// swap
	u2.reset(new Number(42));
	u1.swap(u2);
	assert(!u2);
	assert(u1->n == 42);
	assert(Number::ctr == 1);
	
	// make unique
	u2 = MakeUnique(u1->n * 10);
	assert(u2->n == 420);
	assert(Number::ctr == 2);
}

int main()
{
	// test for std::unique_ptr
	std::cout << "Testing std::unique_ptr..." << std::endl;
	unique_ptr_test<std::unique_ptr<Number>, std::make_unique<Number>>();
	assert(Number::ctr == 0);
	std::cout << "std::unique_ptr test passes" << std::endl;
	
	// test for karun::unique_ptr
	std::cout << "Testing karun::unique_ptr..." << std::endl;
	unique_ptr_test<karun::unique_ptr<Number>, karun::make_unique<Number>>();
	assert(Number::ctr == 0);
	std::cout << "karun::unique_ptr test passes" << std::endl;
}
