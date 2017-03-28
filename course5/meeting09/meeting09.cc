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
	List();
	void hello() { std::cout << "size of object is " << sizeof(T) << std::endl; }
};

template<typename T>
List<T>::List()
{
	std::cout << "hello! sizeof(T)=" << sizeof(T) << std::endl;
}

template<>
List<int>::List() // full function specialization
{
	std::cout << "hello from int list!" << std::endl;
}

template<typename P>
struct List<P*>
{
	List() { std::cout << "boo" << std::endl; }
	void hello() { std::cout << "size of pointed-to object is " << sizeof(P) << std::endl; }
};

int main(int /*argc*/, char** /*argv*/)
{
	List<int> li;
	List<std::string> ls;
	List<double*> ldp;
	List<char*> lcp;
	
	li.hello();
	ls.hello();
	ldp.hello();
	lcp.hello();
}


