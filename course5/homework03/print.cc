#include <cstdio>
#include <string>
#include "print.h"

void print(int x)
{
	std::printf("%d\n", x);
}

void print(long l)
{
	std::printf("%ld\n", l);
}


void print(bool b)
{
	if (b)
		std::printf("true\n");
	else
		std::printf("false\n");
}

void print(char c)
{
	std::printf("%c\n", c);
}

void print(float f, int precision)
{
	std::string formatter = "%."+ std::to_string(precision) + "f\n";
	std::printf(formatter.c_str(), f);
}

void print(double d, int precision)
{
	std::string formatter = "%."+ std::to_string(precision) + "lf\n";
	std::printf(formatter.c_str(), d);
}

void print(const char* str)
{
	std::printf("%s\n", str);
}

void print(std::string s)
{
	std::printf("%s\n", s.c_str());
}
