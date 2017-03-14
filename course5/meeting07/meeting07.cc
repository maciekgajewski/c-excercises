#include <iostream>
#include <memory>
#include <cassert>

#include "my_class.hh"


int main(int /*argc*/, char** /*argv*/)
{
	Course::MyClass o1, o2;
	o1.x = 7;
	o2.x = 5;
	
	
	std::cout << (o1 + o2).GetX() << std::endl; // 
		// Course::MyClass::GetX() const
}

