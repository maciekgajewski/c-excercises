#include <cstdio>
#include <string>

/***
Imagine that you are a young C++ developer, and your manager, for some reason, forbids std::cout. The only I/O function you are allowed to use to produce the output, is std::printf from <cstdio>

You are not happy about it; you are using C++ after all, and you want to take advantage of the type-safety and convenience it offers.

1. Write a library that provides you with “print”, a function you can use on a selection of types: int, bool, string, float, double etc. The function would use std::printf under the covers to print the value.
2. For floating-point values, the function could take a second, optional parameter, integer, that specifies the precision with which the number is printed.
***/
namespace printer
{
	/***
	provides overloaded function to print various types to stdout
	***/
	void print(int input)
	{
		std::printf("%i", input);
	}

	void print(double input, int precision = 0)
	{
		std::string format_str = "%." + std::to_string(precision) + "f";
		const char * format_ptr = format_str.c_str();
		std::printf(format_ptr, input);
	}

	void print(bool input)
	{
		if (input)
			std::printf("true");
		else
			std::printf("false");
	}

	void print(const char * input)
	{
		std::printf("%s", input);
	}

	void print(std::string input)
	{
		std::printf("%s", input.c_str());
	}

}

int main()
{
	using namespace printer;

	// comment indicates the expected input
	print(7); // 7
	print(true); // true
	print(false); // false
	print(1.0/3.0, 2); // 0.33

	std::string s = "world!";
	print("hello, "); // hello,
	print(s); // world!

	float f = 6;
	print(f); // 6

	double d = 6;
	print(d); // 6
}
