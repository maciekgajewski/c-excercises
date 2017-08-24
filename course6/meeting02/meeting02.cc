#include <iostream>
#include <cstdint>

int g = 77;

void print(int i) { std::cout << "int: " << i << std::endl; }
void print(double d) { std::cout << "double: " << d << std::endl; }

// using value = double;
// int print(value d) { std::cout << "value: " << d << std::endl; return 6; }

int main(int argc, char** argv)
{
	int a = 7;
	std::uint64_t b = 88;
	double c = 3.14;
	float d = 6.77;

	print(a);
	print(b);
	print(c);
	print(d);
}

