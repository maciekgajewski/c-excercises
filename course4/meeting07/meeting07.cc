#include <iostream>
#include <string>

template<typename T>
void foo(T t)
{
}

int main()
{
	std::cout << "yo" << std::endl;
	
	double d = 6.5;
	const char* text = "Hello";
	std::string s = text;
	const std::string& cref = s;
	
	foo(d);
	foo(text);
	foo(s);
	foo(cref);
}