#include <iostream>
#include <string>
#include <iomanip>
#include <cstring>

using namespace std::literals;

template<typename T>
std::string type_name()
{
	return "unknown";
}

template<typename T>
int something(const T& a)
{
	if (type_name<T>() == "int")
		return a;
		
	if (type_name<T>() == "std::string")
	{
		return a.length();
	}
}

template<typename T>
bool is_larger(const T& a, const T& b)
{
	std::cout << "comparing two objects of type " << type_name<T>() << std::endl;
	return a > b;
}

bool is_larger(const char* a, const char* b)
{
	return std::strcmp(a, b) > 0;
}

template<>
std::string type_name<int>() { return "int"; }
template<>
std::string type_name<double>() { return "double"; }

int main(int /*argc*/, char** /*argv*/)
{
	std::cout << type_name<int>() << std::endl;
	std::cout << type_name<double>() << std::endl;
	std::cout << type_name<char>() << std::endl;

	std::cout << std::boolalpha;
	std::cout << is_larger(6, 8) << std::endl;
	std::cout << is_larger(66.6, 8.8) << std::endl;
	std::cout << is_larger<double>(66.6, 8) << std::endl;
	std::cout << is_larger<const char*>("aaa", "zzz") << std::endl;
	std::cout << is_larger("aaa"s, std::string("zzz")) << std::endl;
	std::cout << is_larger("aaa", "zzz") << std::endl;
	std::cout << is_larger("zzz", "aaa") << std::endl;


	/*
	println(7);
	println(8.8);
	println("Hello!");
	println(7, 8.8, "hello");
	println("str"s, 77);
	*/
	
	
	
}

template<typename ... T>
void println(T... v)
{
	std::cout << "println" << std::endl;
}

