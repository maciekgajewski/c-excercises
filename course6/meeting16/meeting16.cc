#include <iostream>
#include <string>
#include <stdexcept>

int divide(int a, int b)
{
	if (b == 0)
		throw std::invalid_argument("Division by zero");
	return a/b;
}

int sum(int a, int b) { return a+b; }

int main(int argc, char** argv)
{
	if (argc < 4)
		throw std::runtime_error("At least 3 arguments required");

	int a = std::stoi(argv[1]);
	int b = std::stoi(argv[2]);
	int c = std::stoi(argv[3]);
	
	int result = sum(divide(a, b), c);;

	std::cout << a << " / " << b << " + " << c << " = " << result << std::endl;
}
 