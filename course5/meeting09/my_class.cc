#include "my_class.hh"
#include <iostream>
namespace Course {


int MyClass::GetX() const { return x; }

// Course::MyClass Course::operator+(Course::MyClass, Course::MyClass)
MyClass operator+(MyClass a, MyClass b)
{
	MyClass result;
	result.x = a.x + b.x;
	
	//println(result.x);
	
	return result;
}


	
}
