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
	int inArgs = std::count(argv, argv+argc, std::string("Ariel"));
	std::cout << "Ariels in arguments: " << inArgs << std::endl;
	
	std::list<std::string> l{"aa", "bb", "cc"};
	int inList = std::count(l.begin(), l.end(), 66);
	std::cout << "Ariels in list: " << inList << std::endl;
}

 