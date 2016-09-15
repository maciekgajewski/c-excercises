#include <iostream>
#include <string>

int main(int argc, char** argv)
{
	auto a = 33ll;
	auto b = 4.5;
	auto c = "hel\0lo"; // const char*
	
	auto d = *c; // const char
	auto e = c + 4;
	auto f = c[1];
	auto g = std::string("hello");
	auto h = g[1];
	
	std::cout << g << std::endl;
	std::cout << 3["hello"] << std::endl;
	
}

