#include "complex.hh"

#include <iostream>
#include <string>
#include <cstring>

template<typename T>
const char* GetTypeName() { return "Unknown type"; }

template<>
const char* GetTypeName<int>() { return "int"; }
template<>
const char* GetTypeName<double>() { return "double"; }
template<>
const char* GetTypeName<const char*>() { return "cstr"; }


template<typename T>
T Max(T a, T b)
{
	std::cout << "DEBUG: called Max with T=" << GetTypeName<T>() << std::endl;

	if (a > b) return a;
	else return b;
}

template<>
const char* Max<const char*>(const char* a, const char* b)
{
	if (std::strcmp(a, b) > 0) return a;
	else return b;
}



int main(int argc, char** argv)
{
	std::cout << GetTypeName<double>() << std::endl;

	std::cout << Max("Avid", "Mart") << std::endl;
	std::cout << Max(7.6f, 8.8f) << std::endl;
}


