#include <iostream>
#include <cstdint>

int g = 77;

int main(int argc, char** argv)
{
	int a = 7;
	std::uint64_t b = 88;
	double c = 3.14;
	auto d = 2.71;
	auto e = 5.6f;

	std::uint64_t* f = &b;
	double* g = &c;

	std::cout << "c=" << c << std::endl;
	std::cout << "d=" << d << std::endl;

	c = b;
	std::cout << "c=" << c << std::endl;
	std::cout << "d=" << d << std::endl;

	*g = 6.7;
	std::cout << "c=" << c << std::endl;
	std::cout << "d=" << d << std::endl;

	g = &d;
	*g = 612.34;
	std::cout << "c=" << c << std::endl;
	std::cout << "d=" << d << std::endl;

	g = &b
}

