#include <iostream>
#include <stdexcept>
#include <memory>

int divide(int a, int b)
{
	if (b != 0)
		return a/b;
	else
		throw std::runtime_error("Divison by zero");
}

struct S
{
	S() { std::cout << "S created" << std::endl; }
	~S() { std::cout << "S destroyed" << std::endl; }
};

int main(int argc, char** argv)
{
	if (argc < 3)
	{
		std::cerr << "2 params required!" << std::endl;
		return 1;
	}
	
	try
	{
		auto s = std::make_unique<S>();
		std::cout << divide(std::stoi(argv[1]), std::stoi(argv[2])) << std::endl;
		std::cout << "boo!" << std::endl;
	}
	catch(...)
	{
		std::cerr << "Error!" << std::endl;
		return 1;
	}
	
	return 0;
}

