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

	try
	{
		int a, b, c;
		try
		{
			a = std::stoi(argv[1]);
			b = std::stoi(argv[2]);
			c = std::stoi(argv[3]);
		}
		catch(...)
		{
			std::cout << "Error reading arguments" << std::endl;
			throw;
		}
			
		int result = sum(divide(a, b), c);;

		std::cout << a << " / " << b << " + " << c << " = " << result << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
}
 