#include <iostream>

int main(int argc, char** argv)
{
	// TODO - iterate over argv, print every element
	char** end = argv + argc;
	char** ptr = argv;
	for (; ptr != end; ptr++)
	{
		std::cout << *ptr << std::endl;
	}
}

 