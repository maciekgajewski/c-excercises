#include <iostream>
#include <string>

void print()
{
	std::cout << std::endl;
}


template<typename Arg0, typename... Args>
void print(const Arg0& arg0, const Args&... aa)
{
	std::cout << arg0;
	print(aa...);
}

double add()
{
	return 0;
}

template<typename Arg0, typename... Args>
double add(const Arg0& arg0, const Args&... aa)
{
	return arg0 + add(aa...);
}


int main()
{
 	print(7, "Hello", 6.6);
	std::cout << 7;
	std::cout << "Hello";
	std::cout << 6.6;
	std::cout << std::endl;
	
	
	std::cout << add(7, 8, 9.9, 0) <<std::endl;
	
	double x = 6.6;
	
	print("addr of x = " , &x);
	
	std::string s = "qwert";
	print("length of ", s, " is ", s.length());
	
	print();
	
	
}