#include <iostream>
#include <algorithm>
#include <cstring>

int main(int argc, char** argv)
{
	std::sort(argv, argv+argc,
		[](const char* a, const char* b)
		{
			return std::strcmp(a, b) < 0; 
		});
	
	for(int i = 0; i < argc; i++)
		std::cout << argv[i] << std::endl;
	
}
