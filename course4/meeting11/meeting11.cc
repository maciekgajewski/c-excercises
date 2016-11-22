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

// convers c-strings to int and divide
int divide_strings(const char* a, const char* b)
{
	auto s = std::make_unique<S>();
	int res = divide(std::stoi(a), std::stoi(b));
	std::cout << "foo!" << std::endl;
	return res;
}

int main(int argc, char** argv)
{
	if (argc < 3)
	{
		std::cerr << "2 params required!" << std::endl;
		return 1;
	}
	
	try
	{
		std::cout << divide_strings(argv[1], argv[2]) << std::endl;
		std::cout << "boo!" << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
	catch(const std::runtime_error& re)
	{
		std::cerr << "Runtime error: " << re.what() << std::endl;
		return 1;
	}
	
	return 0;
}

