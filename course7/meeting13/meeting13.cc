#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int main(int argc, char** argv)
{
	std::vector<std::string> params(argv, argv+argc);

	int num_waldos = std::count(params.begin(), params.end(), "Waldo");
	std::cout << "Waldos found: " << num_waldos << std::endl;
}


