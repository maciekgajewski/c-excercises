#include <iostream>
#include <algorithm>
#include <cstring>

int main(int argc, char** argv)
{
	char** start = argv+1;
	int mul = 1;
	if (std::strcmp(argv[1], "-d") == 0)
	{
		start = argv+2;
		mul = -1;
	}
	
	std::sort(start, argv+argc,
		[=](const char* a, const char* b)
		{
			return mul*std::strcmp(a, b) < 0; 
		});
	
	std::for_each(start, argv+argc, [](const char* a) {
		std::cout << a << std::endl; });

}
