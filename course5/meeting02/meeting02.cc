#include <iostream>


int main(int argc, char** argv)
{
	int i = 6;
	int& r = i;
	auto x = r;
	
	r = 7;
	
	int x = r;
	
	auto p = &r;
	
	std::cout << "i=" << i << std::endl;
	std::cout << "r=" << r << std::endl;
	std::cout << "*p=" << *p << std::endl;
}

