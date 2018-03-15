#include <iostream>
#include <string>
#include <set>
#include <unordered_set>

int main(int argc, char** argv)
{
	std::string greeting = "Hello, world!";
	std::unordered_set<char> chars(greeting.begin(), greeting.end());

	for(char c : chars)
		std::cout << c;
	std::cout << std::endl;

	// searching!
	if (argc > 1)
	{
		char search = argv[1][0];
		auto it = chars.find(search);
		if (it == chars.end())
			std::cout << search << " not found" << std::endl;
		else
		{
			std::cout << search << " found" << std::endl;
			chars.erase(search);
		}

		for(char c : chars)
			std::cout << c;
		std::cout << std::endl;
	}

}


