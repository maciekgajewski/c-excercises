#include <iostream>
#include <memory>
#include <cassert>
#include <string>

#include "my_class.hh"


using namespace std::literals;

template<typename T>
void println(const T& v)
{
	std::cout << v << std::endl;
}

struct MyString
{
	bool empty() { return false; }
};

int main(int /*argc*/, char** /*argv*/)
{
	println(7);
	println(8.8);
	println("Hello!");
	
}

