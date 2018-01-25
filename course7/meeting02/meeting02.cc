#include <iostream>
#include <stdexcept>
#include <string>

int fib(int i)
{
	if (i < 2)
		return 1;
	else
		return fib(i-1) + fib(i-2);
}

int main(int argc, char** argv)
{
	if (argc < 2)
		throw std::runtime_error("Not enough params");

	std::string arg1 = argv[1];
	int i = std::stoi(arg1);

	std::cout << "fib(" << i << ") = " << fib(i) << std::endl;
}
