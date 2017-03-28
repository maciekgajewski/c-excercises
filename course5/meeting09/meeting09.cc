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

int main(int /*argc*/, char** /*argv*/)
{
	println(7);
	println();
	println(8.8);
	println("Hello!");
	println(7, 8.8, "hello");
	println("str"s, 77);
}


