#include <cstdio>
#include <string>
#include <iostream>

void print(int x)
{
	std::printf("%d\n", x);
}

void print(long x)
{
	std::printf("%ld\n", x);
}

void print(bool x)
{
	std::printf("%s\n", x ? "true" : "false");
}

void print(const std::string x)
{
	std::printf("%s\n", x.c_str());
}

void print(const char* x)
{
	std::printf("%s\n", x);
}


void print(double x, int prec = 0)
{
	std::printf("%.*f \n", prec, x);
}


int main()
{
	// comment indicates the expected input
	print(7); // 7
	print(true);// true
	print(1.0/3.0, 2);// 0.33
	
	std::string s = "word!";
	print("hello, "); // hello, 
	print(s); // world!

	float f = 6;
	print(f); // 6
}