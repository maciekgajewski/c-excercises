#include <iostream>
#include <string>

double foo()
{
	std::cout << "I'm foo" << std::endl;
	return 3.3;
}

double bar()
{
	std::cout << "bar" << std::endl;
	return 6.6;
}
	

void hey(int a, int b)
{
}
	
int main(int argc, char** argv)
{
	double(*p1)() = &foo;
	
	auto x = p1();
	p1 = &bar;
	std::cout << p1() << std::endl;
	
	p1 = &hey;
	std::cout << p1() << std::endl;
}
