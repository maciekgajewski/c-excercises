#include <iostream>

#include <vector>
#include <array>
#include <list>
#include <deque>

template<typename Iterator>
void print_range(Iterator b, Iterator e)
{
	for(Iterator arg = b; arg != e; arg++)
	{
		std::cout << std::boolalpha << *arg << std::endl;
	}
}

template<typename Range>
void print(const Range& range)
{
	print_range(std::begin(range), std::end(range));
}


int main(int argc, char** argv)
{
	std::cout << "Hello" << std::endl;
	auto x = argc + argv;
	print_range(argv, x);
	
	std::vector<std::string> strings;
	strings.push_back("One");
	strings.push_back("Two");
	strings.push_back("Three");
	strings.push_back("Four");
	
	print_range(strings.begin() + 2, strings.begin()+4);

	std::list<int> ints;
	ints.push_back(4);
	ints.push_back(7);
	
	print_range(ints.begin(), ints.end());
	
	std::deque<double> dbls;
	dbls.push_back(3.14);
	dbls.push_back(77.77);

	print(dbls);
	
	std::array<bool, 3> bools;
	bools[0] = true;
	bools[1] = false;
	bools[2] = true;

	print_range(bools.begin(), bools.end());

	int array[2] = { 6, 8 };
	print(array);

	//for(auto x : array)
	for(auto it = std::begin(array); it != std::end(array); ++it)
	{ 
		auto x = *it;
		
		std::cout << x << std::endl;
	}
	
}

