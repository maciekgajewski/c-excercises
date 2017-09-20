#include <iostream>
#include <string>
#include <array>

void fun(const std::array<int, 3>& p)
{
	std::cout << sizeof(p) << std::endl;
	//p[0] = 66;
	std::cout << p[2] << std::endl;
	std::cout << " in fun " << std::endl;
	for(auto x : p)
		std::cout << x << std::endl;

}

std::array<int, 4> array()
{
	return {0, 1, 3, 4};
}

void print(std::string s)
{
	s[0] = 'X';
	std::cout << s << std::endl;
}

int main(int argc, char** argv)
{
	std::array<int, 3> a = { 1, 3, 5};
	std::cout << sizeof(a) << std::endl;
	std::cout << a[2] << std::endl;
	fun(a);
	std::cout << " in main " << std::endl;
	for(auto x : a)
		std::cout << x << std::endl;
	fun({6, 6, 6});
	print("abc");
}

