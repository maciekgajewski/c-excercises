#include <iostream>
#include "my_unique_ptr.h"
int main()
{
	//MyUniquePtr<std::string> p(new std::string("Hello"));
	auto p = MyMakeUnique<std::string>(7, 'x');
	MyUniquePtr<std::string> copy = std::move(p);
	
	//MyUniquePtr<std::string[]> array(new std::string[4]);
	MyUniquePtr<std::string[]> array = MyMakeUnique<std::string[]>(4);
	
	std::cout << *copy << std::endl;
	std::cout << "length=" << copy->length() << std::endl;
	
	array[0] = "yo";
	std::cout << array[0] << std::endl;
}
