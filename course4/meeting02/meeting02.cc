#include <iostream>
#include <string>

struct S
{
	int i;
	double d;
};

void triple(int& i)
{
	i *= 3;
}

int main(int argc, char** argv)
{
	int a = 7;
	int b = 8;
	S x = { 1, 3.14 };
	
	int* p = &a;
	int& r = a;
	
	S* sp = &x;
	S& sr = x;
	
	triple(a);
	triple(b);
	
	std::cout << sr.i  << sp->i << std::endl;
	
}

