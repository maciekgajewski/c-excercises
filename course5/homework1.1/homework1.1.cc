#include <iostream>
#include <set>

int main(int argc, char** argv)
{
	std::set<std::string> words;

	for (int argIdx = 1; argIdx < argc; argIdx += 1)
	{
		words.emplace(argv[argIdx]);
	}

	for (auto word : words)
	{
		std::cout << word << std::endl;
	}
}
