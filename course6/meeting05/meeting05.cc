#include <iostream>
#include <string>



int main(int argc, char** argv)
{
	std::cout << "Hello" << std::endl;

	int a[3] = { 1, 3, 5};
	std::cout << sizeof(a) << std::endl;

	std::string b[4] = { "abc", "b", "c", "d" };

	for(auto x : b[0])
		std::cout << x << std::endl;

	for(auto x : a)
		std::cout << x << std::endl;
	for(auto& x : b)
		std::cout << x << std::endl;
}

