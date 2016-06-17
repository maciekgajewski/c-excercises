#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include <iterator>

#include <boost/range/algorithm.hpp>

template<typename T>
struct BiggerThanN
{
	bool operator()(T v)
	{
		return v > mN;
	}
	
	T mN;
};

int main(int argc, char** argv)
{
	std::vector<int> vec = { 1, 4, 5, 6, 7, 8, 9};
	
	auto biggerThan6 = boost::count_if(vec, BiggerThanN<int>{6});// BiggerThanN
	auto biggerThan9 = std::count_if(vec.begin(), vec.end(), BiggerThanN<int>{9});// BiggerThanN
	int X = 4;
	
	std::list<std::string> strings = {"a", "list", "of", "Strings"};
	int biggerThanC = std::count_if(strings.begin(), strings.end(), BiggerThanN<std::string>{"c"});
	std::cout << "bigger than C: " << biggerThanC << std::endl;
	
	auto lambda = [X, &argc](int n){ return n > X; } ;
	auto biggerThan4 = std::count_if(vec.begin(), vec.end(), lambda);//  
	
	std::cout << "Vector content:" << std::endl;
	std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, ", "));
	std::cout << std::endl;
	std::cout << "elements >6: " << biggerThan6 << std::endl;
	std::cout << "elements >9: " << biggerThan9 << std::endl;
	std::cout << "elements >4: " << biggerThan4 << std::endl;
	
	
}