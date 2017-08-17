#include <iostream>
#include <cstdint>

int g = 77;

void fun(int arg)
{
	if (arg == 0)
		return;
	int a = 7;
	int b = 7;

	std::cout << "&a=" << &a << std::endl;
	std::cout << "&b=" << &b << std::endl;
	std::cout << "&arg=" << &arg << std::endl;
	std::cout << "&g=" << &g << std::endl;
	std::cout << std::endl;
	fun(arg-1);
}

int main(int argc, char** argv)
{
	fun(argc);
}

