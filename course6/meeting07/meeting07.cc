#include <iostream>
#include <string>
#include <cstring>

using namespace std::literals;

// int max(int a, int b) { return a < b ? b : a; }
// double max(double a, double b) { return a < b ? b : a; }
// std::string max(std::string a, std::string b) { return a < b ? b : a; }

template<typename T>
T Max(const T& a, const T& b)
{
	if (a < b)
		return b;
	else
		return a;
}

const char* Max(const char* a, const char* b)
{
	if (std::strcmp(a, b) < 0)
		return b;
	else
		return a;
}

int main(int argc, char** argv)
{
	std::cout << Max<int>(7, 99) << std::endl;
	std::cout << Max(5.5, 42.7) << std::endl;
	std::cout << Max("Ariel"s, "Maciek"s) << std::endl;
	std::cout << Max<const float>(1, 1.1) << std::endl;

	std::cout << Max<const char*>("Aris", "Misha") << std::endl;
}

