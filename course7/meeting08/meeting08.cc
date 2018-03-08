#include "complex.hh"

#include <iostream>
#include <string>
#include <cstring>

template<typename T>
const char* GetTypeName() { return "Unknown type"; }

template<>
const char* GetTypeName<int>() { return "int"; }
template<>
const char* GetTypeName<float>() { return "float"; }
template<>
const char* GetTypeName<double>() { return "double"; }
template<>
const char* GetTypeName<const char*>() { return "cstr"; }


template<typename T>
T Max(T a, T b)
{
	std::cout << "DEBUG: called Max with T=" << GetTypeName<T>() << std::endl;

	if (b < a) return a;
	else return b;
}

template<>
const char* Max<const char*>(const char* a, const char* b)
{
	if (std::strcmp(a, b) > 0) return a;
	else return b;
}


template<typename T>
Complex<T> add(Complex<T> a, Complex<T> b)
{
	std::cout << "DEBUG: adding Complex<T> T=" << GetTypeName<T>() << std::endl;
	return Complex<T>(a.mR + b.mR, a.mI + b.mI);
}

template<typename CT>
CT sub(CT a, CT b)
{
	std::cout << "DEBUG: substracting Complex<T> T=" << GetTypeName<typename CT::storage_type>() << std::endl;
	return CT(a.mR - b.mR, a.mI - b.mI);
}

int main(int argc, char** argv)
{
	Complex<float> c1(3, 6.7);
	Complex<float> c2(3.7, 6);

	std::cout << add(c1, c2) << std::endl;
	std::cout << sub(c1, c2) << std::endl;
}


