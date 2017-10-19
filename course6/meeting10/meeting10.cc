#include <iostream>
#include <string>
#include <vector>
#include <list>

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
	print(argv, argv + argc);

	std::vector<int> v({1, 3, 5, 7, 9});
	print(v.begin(), v.end());

	std::list<std::string> l{"aa", "bb", "cc"};
	print(l.begin(), l.end());

}

 