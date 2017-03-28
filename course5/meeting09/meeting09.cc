#include <iostream>
#include <string>
#include <iomanip>
#include <cstring>

using namespace std::literals;

template<typename T>
bool is_larger(const T& a, const T& b)
{
	return a > b;
}

bool is_larger(const char* a, const char* b)
{
	return std::strcmp(a, b) > 0;
}

template<typename T>
std::string type_name();

int main(int /*argc*/, char** /*argv*/)
{

	std::cout << std::boolalpha;
	std::cout << is_larger(6, 8) << std::endl;
	std::cout << is_larger(66.6, 8.8) << std::endl;
	std::cout << is_larger<double>(66.6, 8) << std::endl;
	std::cout << is_larger<const char*>("aaa", "zzz") << std::endl;
	std::cout << is_larger("aaa"s, std::string("zzz")) << std::endl;
	std::cout << is_larger("aaa", "zzz") << std::endl;
	std::cout << is_larger("zzz", "aaa") << std::endl;


	std::cout << type_name<int>() << std::endl;



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

