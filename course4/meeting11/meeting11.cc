#include <iostream>
#include <stdexcept>
#include <memory>
#include <cassert>

struct Price
{
	int mValue;
	std::string currency;
	
};
static_assert(sizeof(Price) == sizeof(int), "Price should be the size of one integer");

int divide(int a, int b)
{
	assert(b != 0 && "Attempt to divide by zero");
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

void log_exception()
{
	std::cerr << "Error in divide_strings" << std::endl;
	throw;
}

// convers c-strings to int and divide
int divide_strings(const char* a, const char* b)
{
	try{
		auto s = std::make_unique<S>();
		int res = divide(std::stoi(a), std::stoi(b));
		std::cout << "foo!" << std::endl;
		return res;
	}
	catch(...)
	{
		log_exception();
	}
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
	catch(const std::logic_error& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
	
	return 0;
}

