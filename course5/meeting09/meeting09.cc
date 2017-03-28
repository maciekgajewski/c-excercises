#include <iostream>
#include <string>
#include <iomanip>
#include <cstring>

using namespace std::literals;

void println()
{
	std::cout << std::endl;
}

template<typename T0, typename... T>
void println(T0 v, T... rest)
{
	std::cout << v;
	println(rest...);
}

template<typename T>
struct List
{
	static void hello() { std::cout << "size of object is " << sizeof(T) << std::endl; }
};

template<typename P>
struct List<P*>
{
	static void hello() { std::cout << "size of pointed-to object is " << sizeof(P) << std::endl; }
};

template<typename T>
struct remove_ptr
{
	using type = T;
};

template<typename P>
struct remove_ptr<P*>
{
	using type = P;
};

int main(int /*argc*/, char** /*argv*/)
{
	remove_ptr<int>::type a;
	remove_ptr<double>::type b;
	remove_ptr<int*>::type c;
	remove_ptr<double*>::type d;
	
	
	List<int>::hello();
	List<std::string>::hello();
	List<double*>::hello();
	List<char*>::hello();
}


