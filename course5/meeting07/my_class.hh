#pragma once

namespace Course
{

struct MyClass
{
	int GetX() const;
	double length() const;
	int x;
};

template<typename T>
void println(const T& v);


MyClass operator+(MyClass a, MyClass b);
// Course::operator+(Course::MyClass, Course::MyClass)
}