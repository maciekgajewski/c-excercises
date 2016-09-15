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

void printFirstAndLast(int a[])
{
	std::cout << a[0] << ", " << a[4] << std::endl;
	std::cout << sizeof(a) << std::endl; 
	a[0] = 7;
}
	
int main(int argc, char** argv)
{
	int a[5] = { 1, 2, 3, 4, 5 };
	
	a[0] = 6;
	
	
	a[77777] = 66;
	
	printFirstAndLast(a);
	printFirstAndLast(a);
	
}

