#include <iostream>
#include <cassert>

int fib(int x)
{
	std::cout << "fib(" << x << "), addr of x = " << &x << std::endl;
	assert(x > 0);
	if ( x < 2 )
		return 1;
	else
		return fib(x-1) + fib(x-2);
}

int main()
{
	std::cout << fib(5) << std::endl;
}
