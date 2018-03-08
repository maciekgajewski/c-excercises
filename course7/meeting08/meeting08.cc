#include "complex.hh"

#include <iostream>
#include <string>
#include <cstring>

template<typename T>
struct GetType {
	static const char* Name() { return "Unknown type"; }
};

template<>
struct GetType<int> {
	static const char* Name() { return "int"; }
};

template<>
struct GetType<float> {
	static const char* Name() { return "float"; }
};

template<>
struct GetType<double> {
	static const char* Name() { return "double"; }
};

template<>
struct GetType<const char*> {
	static const char* Name() { return "const char*"; }
};

template<typename X>
struct GetType<X*> {
	static std::string Name() { return std::string("Pointer to ") + GetType<X**>::Name() ; }
};


template<typename T>
T Max(T a, T b)
{
	std::cout << "DEBUG: called Max with T=" << GetType<T>::Name() << std::endl;

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
	std::cout << "DEBUG: adding Complex<T> T=" << GetType<T>::Name() << std::endl;
	return Complex<T>(a.mR + b.mR, a.mI + b.mI);
}

template<typename CT>
CT sub(CT a, CT b)
{
	std::cout << "DEBUG: substracting Complex<T> T=" << GetType<typename CT::storage_type>::Name() << std::endl;
	return CT(a.mR - b.mR, a.mI - b.mI);
}

int main(int argc, char** argv)
{
	std::cout << GetType<double>::Name() << std::endl;
	std::cout << GetType<double*>::Name() << std::endl;

	Complex<float> c1(3, 6.7);
	Complex<float> c2(3.7, 6);

	std::cout << add(c1, c2) << std::endl;
	std::cout << sub(c1, c2) << std::endl;
}


