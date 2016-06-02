#include <iostream>
#include <stdexcept>

void println()
{
	std::cout << std::endl;
}

template<typename T, typename... Rest>
void println(const T& param0, const Rest&... rest)
{
	std::cout << param0 << ", ";
	println(rest...);
}

int main()
{
	std::string s = "Hello";
	int i = 7;
	const int ci = 8;
	const int& cref = ci;
	
	println(s);
	println(i);
	println(ci);
	println(cref);
	println();
	println(5, 6);
	println(5, 6.0);
    
}