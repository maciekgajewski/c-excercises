#include "my_string.h"

#include <iostream>

int Max(int a, int b)
{
	return a > b ? a : b;
}

double Max(double a, double b)
{
	return a > b ? a : b;
}

bool CanBeInstrumentId(const Maciek::String& s)
{
	return s.size() >= 6 && s[4] == ':';
}

int main()
{
	Maciek::String s = "abc";
	//Maciek::String x = "123";
	//s = std::move(x);
	s = "1213";
	std::cout << s.c_str() << std::endl;
	
}