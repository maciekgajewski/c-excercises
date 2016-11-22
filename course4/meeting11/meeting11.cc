#include <iostream>


int divide(int a, int b)
{
	return a/b;
}

int main(int argc, char** argv)
{
	if (argc < 3)
	{
		std::cerr << "2 params required!" << std::endl;
		return 1;
	}
	
	std::cout << divide(std::stoi(argv[1]), std::stoi(argv[2])) << std::endl;
	return 0;
}

