#include <iostream>
#include <string>
#include <set>

int main(int argc, char** argv)
{
	std::string greeting = "Hello, world!";
	std::set<char> chars(greeting.begin(), greeting.end());

	for(char c : chars)
		std::cout << c;
	std::cout << std::endl;
}


