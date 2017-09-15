#include <iostream>
#include <string>

int main(int argc, char** argv)
{
	std::cout << "Hello" << std::endl;

	int a[3];
	std::cout << sizeof(a) << std::endl;

	std::string b[4] = { "a", "b", "c", "d" };
	std::cout << "sizeof b: " << sizeof(b) << std::endl;
	std::cout << "sizeof string: " << sizeof(std::string) << std::endl;

	std::cout << "b[2] = " << b[2] << std::endl;
	b[2] = "yo";
	std::cout << "b[2] = " << b[2] << std::endl;

	std::string ari;

	ari = "Hello";
	std::cout << "ari length: " << ari.length() << ", data: " << (void*)ari.data() << std::endl;
	ari += ", world!";
	std::cout << "ari length: " << ari.length() << ", data: " << (void*)ari.data() << std::endl;
	ari = "x123456789012345678901234567890";
	std::cout << "ari length: " << ari.length() << ", data: " << (void*)ari.data() << std::endl;
	std::cout << ari << std::endl;
}

