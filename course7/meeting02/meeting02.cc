#include <iostream>
#include <stdexcept>
#include <string>

void print(int i)
{
	std::cout << "int: " << i << std::endl;
}

void print(float i)
{
	std::cout << "float: " << i << std::endl;
}

void dbl(int& i)
{
	i *= 2;
}

void print(std::string& s)
{
	std::cout << "string: " << s << std::endl;
}

int main(int argc, char** argv)
{
	int* p = nullptr;
	int i = 77;
	int& r = i;
	p = &i;

	r = 66;
	dbl(i);
	dbl(r);
	print(i);

	print("abc");

}
