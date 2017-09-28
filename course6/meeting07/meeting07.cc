#include <iostream>
#include <string>
#include <cstring>

#include "vector.hh"

template<typename T>
struct Type
{
	static std::string name();
};

template<>
struct Type<int>
{
	static std::string name() { return "int"; }
};

template<>
struct Type<double>
{
	static std::string name() { return "double"; }
};

template<typename X>
struct Type<X*>
{
	static std::string name() { return "pointer to " + Type<X>::name(); }
};

int main(int argc, char** argv)
{
	std::cout << Type<double***>::name() << std::endl;
}

