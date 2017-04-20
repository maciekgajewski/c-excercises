#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

// functor


int main(int argc, char** argv)
{
	std::vector<std::string> strings(argv, argv+argc);
	
	auto it = std::find(strings.begin(), strings.end(), "Waldo");
	if (it == strings.end())
		std::cout << "No Waldo :(" << std::endl;
	else
		std::cout << "Waldo found at pos " << it - strings.begin() << std::endl;
}
