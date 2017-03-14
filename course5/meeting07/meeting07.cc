#include <iostream>
#include <memory>
#include <cassert>
#include <string>

#include "my_class.hh"

template<typename T>
T Add(const T& a, const T& b)
{
	std::cout << "TT" << std::endl;
	return a + b;
}

template<typename T, typename U>
auto Add(const T& a, const U& b)
{
	std::cout << "TU" << std::endl;
	return a + b;
}

std::string Add(const char* a, const char* b)
{
	return std::string(a) + std::string(b);
}

using namespace std::literals;

int main(int /*argc*/, char** /*argv*/)
{
	auto a = Add/*<std:string>*/(std::string("Hello, "), "World!"s);
	auto b = Add(5, 66.6);
	auto c = Add("one", "two");
	
}

