#include <iostream>
#include <memory>
#include <cassert>
#include <string>

using namespace std::literals;

template<typename ... T>
void println(T... v)
{
	std::cout << "println" << std::endl;
}

int main(int /*argc*/, char** /*argv*/)
{
	println(7);
	println(8.8);
	println("Hello!");
	println(7, 8.8, "hello");
	println("str"s, 77);
	
}

