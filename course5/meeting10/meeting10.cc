#include <iostream>
#include <string>
#include <iomanip>
#include <cstring>

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
}


