#include <iostream>
#include <string>
#include <cstring>

template<typename T>
T Max(T a, T b)
{
	if (a < b)
		return b;
	else
		return a;
}	

const char* Max(const char* a, const char* b)
{
	if (std::strcmp(a, b) > 0)
		return a;
	else
		return b;
}

int main()
{
	std::cout << "max(12, 56)=" << Max(12, 56) << std::endl;
	std::cout << "max(1.1, 5.6)=" << Max(1.1, 5.6) << std::endl;
	std::cout << "max(abc, xyz)=" << Max(std::string("abc"), std::string("xyz")) << std::endl;
	std::cout << "max(abc, xyz)=" << Max("abc", "xyz") << std::endl;
}

