#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

template<typename Iterator>
void print(Iterator begin, Iterator end)
{
	for (auto ptr = begin; ptr != end; ptr++)
	{
		std::cout << *ptr << std::endl;
	}
}


int main(int argc, char** argv)
{
	std::vector<const char*> l{"aa", "bb", "cc"};
	int numbers[] = {1, 12, 3, 7};

	for(auto it = std::begin(numbers); it != std::end(numbers); ++it)
	{
		auto e = *it;
		std::cout << e << std::endl;
	}

	for(auto e : l) // use this
	{
		std::cout << e << std::endl;
	}
}

 