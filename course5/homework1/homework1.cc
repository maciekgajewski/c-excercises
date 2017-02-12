#include <iostream>

int main(int argc, char** argv)
{
	for (int counter = 0; counter < argc; counter += 1)
	{
		std::cout << counter << std::endl;
	}
}
