#include <iostream>
#include <string>

void fun(int* p)
{
	std::cout << sizeof(p) << std::endl;
	std::cout << p[2] << std::endl;
}

int main(int argc, char** argv)
{
	std::cout << 2["Hello"] << std::endl;

	int a[3] = { 1, 3, 5};
	std::cout << sizeof(a) << std::endl;
	std::cout << a[2] << std::endl;
	for(auto x : a)
		std::cout << x << std::endl;

	int* ptr = a;

	fun(a);
}

