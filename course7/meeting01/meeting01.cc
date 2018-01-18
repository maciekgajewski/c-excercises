#include <iostream>
#include <cstdint>

int main(int argc, char** argv)
{
	// initialization
	int i = 7;
	float f = i;

	int* ip = &i;
	float* fp = &f;

	*ip = 66;
	*fp = 66;

	std::cout << "i=" << i
		<< ", the size of i is: " << sizeof(i)
		<< ", the address of i is: " << ip
		<< std::endl;

	std::cout << "f=" << f
		<< ", the size of f is: " << sizeof(f)
		<< ", the address of f is: " << fp
		<< std::endl;

	std::cout << "ip=" << ip
		<< ", the size of ip is: " << sizeof(ip)
		<< ", the address of ip is: " << &ip
		<< std::endl;

}
