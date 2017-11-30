#include <iostream>
#include <string>
#include <stdexcept>

int divide(int a, int b)
{
	if (b == 0)
		throw std::invalid_argument("Division by zero");
	return a/b;
}

int main(int argc, char** argv)
{
	if (argc < 3)
		throw std::runtime_error("At least 2 arguments required");

	int a = std::stoi(argv[1]);
	int b = std::stoi(argv[2]);

	int result = divide(a, b);

	std::cout << a << " / " << b << " = " << result << std::endl;
}
 