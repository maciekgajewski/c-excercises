#include <iostream>
#include <limits>
#include <string>

template<typename T>
void print(const T& v)
{
	std::cout << v << std::endl;
}

void print(const char* t)
{
	std::cout << "c-string: " << t << std::endl;
}

template<typename T>
struct Vector
{
	T x;
	T y;
	
	T sum() const;
	
};

template<typename T>
T Vector<T>::sum() const { return x + y; }

template<>
double Vector<double>::sum() const { return x / y; }


int main(int argc, char** argv)
{
	print("Hello");
	
	Vector<int> v1{3, 5};
	Vector<std::string> v2{"aaa", "bbbb"};

	print(v1.sum());
	print(v2.sum());
	
	Vector<double> v3{ 100.0, 2.5 };
	print(v3.sum());
	
}

