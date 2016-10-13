#include <iostream>
#include <limits>
#include <string>

template<typename T>
struct TypePrinter;

template<>
struct TypePrinter<int>
{
	static void print() { std::cout << "int" << std::endl; }
};

template<>
struct TypePrinter<double>
{
	static void print() { std::cout << "double" << std::endl; }
};

template<typename P>
struct TypePrinter<P*>
{
	static void print() { std::cout << "pointer to "; TypePrinter<P>::print(); }
};

template<typename T>
struct XXX;

template<typename T>
void print(const T& p)
{
	XXX<T> x;
}

int main(int argc, char** argv)
{
	TypePrinter<int>::print();
	TypePrinter<double>::print();
	TypePrinter<double*>::print();
	TypePrinter<int*>::print();
	
	print(8.0f);
}

