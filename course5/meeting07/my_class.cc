#include "my_class.hh"

using namespace Course;


int MyClass::GetX() const { return x; }

// Course::MyClass Course::operator+(Course::MyClass, Course::MyClass)
MyClass Course::operator+(MyClass a, MyClass b)
{
	MyClass result;
	result.x = a.x + b.x;
	return result;
}

