#include <iostream>
#include <cstdint>

int g = 77;

int main(int argc, char** argv)
{
	std::uint64_t b = 88;
	double c = 3.14;
	auto d = 2.71;

	std::uint64_t* f = &b;
	double* g = &c;

	g = reinterpret_cast<double*>(&b);
	std::cout << *reinterpret_cast<std::uint64_t*>(g) << std::endl;
}

