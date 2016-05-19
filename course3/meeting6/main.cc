#include "my_string.h"

#include <iostream>

int main()
{
	using Maciek::String;

	String a;
	a = "a";
	a = "b";
	

	std::cout << a.c_str() << std::endl;
    
}