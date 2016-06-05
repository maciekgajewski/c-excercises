#include "unique_ptr.h"

#include <cassert>
#include <iostream>
#include <memory>


struct Number
{
	int n;
	static int ctr;
	Number(int _n) : n(_n) { ctr++; }
	Number(int _n1, int _n2) : n(_n1 + _n2) { ctr++; }
	Number(const Number& _n) : n(_n.n) { ctr++; }
	Number(Number& _n) : n(_n.n) { _n.n = 0; ctr++; }
	~Number() { ctr--; }
};
int Number::ctr = 0;

void unique_ptr_test()
{
	{
	// default contructor
	karun::unique_ptr<Number> u1;
	assert(u1.get() == nullptr);
	assert(!u1);
	
	// initialization constructor
	karun::unique_ptr<Number> u2(nullptr);
	assert(!u2);
	assert(Number::ctr == 0);
	
	Number* n_ptr = new Number(42);
	karun::unique_ptr<Number> u3(n_ptr);
	assert(u3);
	assert((*u3.get()).n == 42);
	assert(Number::ctr == 1);
	
	// operator* and operator->
	assert((*u3).n == 42);
	assert(u3->n == 42);
	
	// operator== and operator!=
	assert(u1 == u2);
	assert(u2 != u3);
	assert(u3 != karun::unique_ptr<Number>(new Number(42)));
	assert(Number::ctr == 1);
	
	// move constructor
	karun::unique_ptr<Number> u4 = std::move(u3);
	assert(u4->n == 42);
	assert(u4.get() == n_ptr);
	assert(!u3);
	assert(Number::ctr == 1);
	
	// move assignment operator
	karun::unique_ptr<Number> u5(new Number(u4->n * 10));
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
	
	// make_unique
	u2 = karun::make_unique<Number>(u1->n * 10);
	assert(u2->n == 420);
	assert(Number::ctr == 2);
	
	// make_unique with multiple arguments
	u3 = karun::make_unique<Number>(u1->n, u2->n);
	assert(u3->n == 462);
	assert(Number::ctr == 3);
	
	// make_unique with non-const reference
	Number& n_ref = *u1;
	u4 = karun::make_unique<Number>(n_ref);
	assert(u1->n == 0);
	assert(u4->n == 42);
	assert(Number::ctr == 4);
	}
	
	// unique_ptr objects out of scope
	assert(Number::ctr == 0);
}

int main()
{
	std::cout << "Testing karun::unique_ptr and karun::make_unique..." << std::endl;
	unique_ptr_test();
	std::cout << "Tests pass :)" << std::endl;
}
