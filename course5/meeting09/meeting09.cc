#include <iostream>
#include <string>

using namespace std::literals;

template<typename ... T>
void println(T... v)
{
	std::cout << "println" << std::endl;
}

template<typename T>
bool is_larger(const T& a, const T& b)
{
	return a > b;
}

int main(int /*argc*/, char** /*argv*/)
{
	/*
	println(7);
	println(8.8);
	println("Hello!");
	println(7, 8.8, "hello");
	println("str"s, 77);
	*/
	
	
	
}

