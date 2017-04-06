#include <iostream>
#include <string>
#include <iomanip>
#include <cstring>

template<typename T> struct TP;

void print(char arr[7])
{
	TP<decltype(arr)> x;
	std::cout << arr << std::endl;
}

int main(int /*argc*/, char** /*argv*/)
{
	char hello[] = "Hello!";
	// type of hello: char[7]
	int x[] = {1, 4, 5, 7}; // int[4]
	
	auto hey = hello; // type of hey is const char*
	print(hello);
	print(hey);
	std::cout << hey << std::endl;
	
	std::cout << sizeof(hey) << std::endl;
	
}


