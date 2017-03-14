#pragma once

namespace Course
{

struct MyClass
{
	int GetX() const;
	
	int x;
};

MyClass operator+(MyClass a, MyClass b);
// Course::operator+(Course::MyClass, Course::MyClass)
}