#include <iostream>
#include <string>

namespace course
{

double foo(int x)
{
	std::cout << "I'm course::foo, and x=" << x << std::endl;
	return x * 3;
}

}

// int foo(int i)
// {
// 	std::cout << "I'm foo, and i=" << i << std::endl;
// 	if (i > 0)
// 		return i*2.0;
// 	else
// 		return i;
// }

namespace course 
{
	namespace inner
	{
		
		double bar()
		{
			return foo(6);
		}
	}
	
	
}

int main(int argc, char** argv)
{
	using namespace course;
	
	auto x = ::foo(argc);
	std::cout << "x = " << x << std::endl;
}
