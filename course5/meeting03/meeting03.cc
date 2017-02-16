#include <iostream>
#include <string>

void fun(int, int a = 6)
{
	std::cout << "fun(int)" << std::endl;
}

void fun(float)
{
	std::cout << "fun(float)" << std::endl;
}

int main(int argc, char** argv)
{
	fun(8);
	fun(8.8, 8);
	
	std::cout << std::setprecision(7) << 8.8 << std::endl;
	::printf("%7f", 8.8, 6, 77);
}
