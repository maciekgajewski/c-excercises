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
	
	template<typename X>
	T sumX(const X& c) const;
};

template<>
struct Vector<double>
{
	double a, b;
	int sum() const { return int(a/b); }
};

template<typename T>
T Vector<T>::sum() const { return x + y; }


template<typename T>
template<typename X>
T Vector<T>::sumX(const X& c) const
{
	return x + y + c;
}

int main(int argc, char** argv)
{
	print("Hello");
	
	Vector<int> v1{3, 5};
	Vector<std::string> v2{"aaa", "bbbb"};

	print(v1.sum());
	print(v2.sum());
	
	print(v2.sumX("abc"));
	print(v2.sumX(std::string("zzzz")));
	
	Vector<double> v3{ 100.0, 2.5 };
	print(v3.sum());
	
}

