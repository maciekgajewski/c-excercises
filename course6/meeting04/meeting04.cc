#include <iostream>
#include <iomanip>

int main(int argc, char** argv)
{
	const int v = 7;
	//v = 8; // ILLEGAL
	const int* cp = &v;

	int x = 8;
	int* p2 = &x;

	p2 = const_cast<int*>(&v); // not permitted!
	*p2 = 99;
	std::cout << v << std::endl;
	std::cout << *p2 << std::endl;
	std::cout << std::boolalpha << (p2 == &v) << std::endl;
}

