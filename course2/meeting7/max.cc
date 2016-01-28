#include <iostream>
#include <string>
#include <cstring>
#include <cstdint>



template<typename T>
const T& Max(const T& a, const T& b)
{
	if (b < a)
		return a;
	else
		return b;
}

template<>
const char*& Max<const char*&>(const char*& a, const char*& b)
{
	if (std::strcmp(a, b) > 0)
		return a;
	else
		return b;
}


int main()
{
	std::uint64_t a, b;
	//std::int64_t a, b;
	a = 12;
	b = 56;
	
	std::string A = "aaa";
	std::string B = "bbb";
	
	std::cout << "max(12, 56)=" 
		<< Max(a, b)
		<< ", max(2.3, 4.5)="
		<< Max(2.3, 4.5)
		<< ", max(5.5, 46.6)="
		<< Max<float>(5.5, 7)
		<< "Max(aaa, bbb) =" << Max(A, B)
		<< " Max(xx, aa) =" << Max("aa", "zz")
		<< std::endl;
}

