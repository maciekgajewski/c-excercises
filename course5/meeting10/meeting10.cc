#include <iostream>
#include <string>
#include <iomanip>
#include <cstring>

int main(int /*argc*/, char** /*argv*/)
{
	char hello[] = "Hello!";
	// type of hello: char[7]
	int x[] = {1, 4, 5, 7}; // int[4]
	
	for(int i = 0; i < sizeof(x)/sizeof(*x); i++)
	{
		std::cout << x[i] << std::endl;
	}
	
	int* end = x + 4;
	for(int* p = x; p < end; ++p)
	{
		std::cout << *p << std::endl;
	}
	
	// comp
	// incr
	// add
	// mul
	// deref
}


