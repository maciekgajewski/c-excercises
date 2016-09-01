#include <iostream>

int c = 10;

namespace X
{
	int c = 9;
}

namespace Y
{
	int c = 55;
}

int main()
{
	using namespace X;
	
	int a = 7;
	int b = 8;
	
	std::cout << "a+b = " << a+b+c << std::endl;
}

