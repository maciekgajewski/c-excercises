#include <cstdio>
#include <string>
#include <typeinfo>
#include <iostream>
#include <type_traits>

template <typename T>
void print(T p, int prec = 4)
{
	auto a = p;
	if ( std::is_same<T, int>::value | std::is_same<T, long>::value )
	{
		std::printf("%d\n", a);
		std::printf("%s\n", "int");
	} else if ( std::is_same<T, float>::value | std::is_same<T, double>::value )
	{
		std::printf("%f\n", a);
		std::printf("%s\n", "float");
	} else if ( std::is_same<T, std::string>::value )
	{
		std::printf("%s\n", a);
		std::printf("%s\n", "string");
	} else if ( std::is_same<T, bool>::value )
	{
		if (a == 1)
		{
			std::printf("%s\n", "true");
		}
	//	std::printf("%s\n", a ? "true" : "false");
	} else
	{
		std::printf("%s\n", "unsupported type");
	}
}
// TODO your code goes here

int main()
{
	// comment indicates the expected input
	print(7); // 7
	print(true);// true
	print(1.0/3.0, 2);// 0.33
	
	std::string s = "word!";
	print("hello, "); // hello, 
	print(s); // world!

	float f = 6;
	print(f); // 6
//	std::cout << typeid(typeid(7).name()).name() << std::endl;
//	std::cout << typeid(3.3f).name() << std::endl;
//	std::cout << typeid("hello4").name()[0] << std::endl;
//	std::cout << typeid(ch).name() << std::endl;
//	std::cout << typeid(true).name() << std::endl;
}