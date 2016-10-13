#include <iostream>
#include <cstring>

void print(const char* text)
{
	std::cout << text << std::endl;
}

void print(int i)
{
	std::cout << i << std::endl;
}

void print(double i)
{
	std::cout << i << std::endl;
}

int main(int argc, char** argv)
{
	print("Hello");
	print(argc);
	print(3.14);
	print(2.77f);
}

