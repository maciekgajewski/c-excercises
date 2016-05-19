#include "my_string.h"

#include <iostream>

template<typename T>
T Max(T a, T b)
{
	return a > b ? a : b;
}

template<typename T>
T* Max(T* a, T* b)
{
	throw std::logic_error("Dunno how to compare pointers :(");
}

// const char* Max(const char* a, const char* b)
// {
// 	return std::strcmp(a, b) > 0 ? a : b;
// }

int main()
{
	std::cout << Max(1u, 5u) << std::endl;
	std::cout << Max(1.1, -4.5) << std::endl;
	std::cout << Max("Willis", "Felix") << std::endl;
}