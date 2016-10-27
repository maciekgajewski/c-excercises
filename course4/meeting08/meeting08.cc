#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <string>

#include <boost/range/algorithm.hpp>

template<typename T, int SIZE>
int size_of_array( T  (&array)[SIZE])
{
	return SIZE;
}

int main(int argc, char** argv)
{
	static const int N = 6;
	int a[N] = {3, 1, 4, 1, 5, 9 };
	auto end = a + N;
	
	std::cout << "size of a: " << size_of_array(a) << std::endl;
	
	for(int* i = a; i != end; ++i)
	{
		std::cout<<*(i)<<std::endl;
	}
	
	auto argv_end = argv + argc;
	for(auto it = argv; it != argv_end; ++it)
		std::cout << *it << std::endl;
	
	std::vector<int> v = {1, 3, 5, 7 };
	std::list<int> l = {2, 4, 6, 7, 7};
	
	std::cout << "7s in vec " << std::count(v.begin(), v.end(), 7) << std::endl;
	std::cout << "7s in list " << std::count(l.begin(), l.end(), 7) << std::endl;
	std::cout << "7s in arr " << std::count(a, end, 7) << std::endl;
	
	std::vector<std::string> strings = {"one", "seven"};
	std::cout << "7s in srings " << boost::count(strings, "seven") << std::endl;
	
	for(const auto& a : strings) // here
	{
		std::cout << a << std::endl;
	}
	
	// is actually:
	for(auto it = std::begin(strings); it != std::end(strings); ++it)
	{
		const auto& a = *it;
		
		// ...
	}
	
}


template<typename Range, typename T>
auto count(const Range& r, const T& value)
{
	return std::count(std::begin(r), std::end(r), value);
}