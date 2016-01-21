#include <iostream>
#include <string>
#include <cstring>


double Max(double a, double b)
{
	if (b < a)
		return a;
	else
		return b;
}

int main()
{
	std::cout << "max(12, 56)=" << Max(12, 56) << std::endl;
}

