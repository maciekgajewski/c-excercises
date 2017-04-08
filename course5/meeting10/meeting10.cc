#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <list>
#include <array>
#include <set>

// 	int* end = x + 4;
// 	for(int* p = x; p < end; ++p)
// 	{
// 		std::cout << *p << std::endl;
// 	}

template <typename It> 
void iterate_over(It first, It last)
{
	for (auto i = first; i != last; ++i)
	{
		std::cout << *i << std::endl;
	}
}


int main(int argc, char** argv)
{
	std::string s = argv[0];
	std::vector<int> v = {1, 3, 5, 7};
	std::list<double> l = {1.2, 3.4, 5.6, 7.8};
	std::set<int> set = {1, 5, 3, 8, 9, 2};
	
	char hey[] = {'h', 'e', 'l', 'l', 'o'};
	
	iterate_over(s.begin(), s.end());
	auto i = s.find('g');
	if (i != std::string::npos)
		iterate_over(s.begin(), s.begin() + i);
	
	iterate_over(std::begin(hey), std::end(hey));
	
	iterate_over(argv, argv + argc);
}



