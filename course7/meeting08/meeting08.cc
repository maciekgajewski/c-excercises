#include "complex.hh"

#include <iostream>
#include <string>
#include <cstring>

/*
int Max(int a, int b)
{
	if (a > b) return a;
	else return b;
}

double Max(double a, double b)
{
	if (a > b) return a;
	else return b;
}

std::string Max(const std::string& a, const std::string& b)
{
	if (a > b) return a;
	else return b;
}
*/

/**/
template<typename T>
T Max(T a, T b)
{
	if (a > b) return a;
	else return b;
}

const char* Max(const char* a, const char* b)
{
	if (std::strcmp(a, b) > 0) return a;
	else return b;
}



int main(int argc, char** argv)
{
	std::cout << Max(7, 4) << std::endl;
	std::cout << Max<double>(7.7, 4) << std::endl;
	std::cout << Max("Zavid", "Maciek") << std::endl;
}


