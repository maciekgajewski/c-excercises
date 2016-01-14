#include <iostream>
#include <cstdint>

int main()
{
	std::int64_t a = 7;
	auto b = &a;
	double* c = reinterpret_cast<double*>(b);

		std::cout << *c << std::endl;
}
