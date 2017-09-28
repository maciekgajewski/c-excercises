#include <iostream>
#include <string>
#include <cstring>

using namespace std::literals;

template<typename Type>
std::string type_name(); // primary template

template<>
std::string type_name<int>() { return "int"; }

template<>
std::string type_name<double>() { return "double"; }

template<>
std::string type_name<std::string>() { return "std::string"; }

template<typename T>
void print(const T& v)
{
	std::cout << type_name<T>() << " : " << v << std::endl;
}

struct Boo {};

int main(int argc, char** argv)
{
	print("Thomas"s);
	print(66);

	auto p = std::stol(argv[1]);
	print(p);

	print(Boo{});
}

