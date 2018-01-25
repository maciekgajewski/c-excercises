#include <iostream>
#include <stdexcept>
#include <string>

void print(int i)
{
	std::cout << "int: " << i << std::endl;
}

void print(float i)
{
	std::cout << "float: " << i << std::endl;
}

int main(int argc, char** argv)
{
	int i = 55;
	auto pi = &i;

	float f = 44;
	auto pf = &f;

	std::cout << "*pi = " << *pi << std::endl;
	pi = reinterpret_cast<int*>(pf);
	*pi = *pf;

	print(*pi);
}
