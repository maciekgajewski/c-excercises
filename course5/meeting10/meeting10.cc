#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <list>

// 	int* end = x + 4;
// 	for(int* p = x; p < end; ++p)
// 	{
// 		std::cout << *p << std::endl;
// 	}

template <typename T>
void iterate_over(const T& s)
{
	auto end = s.end();
	for (auto i = s.begin(); i != end; ++i)
	{
		std::cout << *i << std::endl;
	}
}


int main(int /*argc*/, char** argv)
{
	std::string s = argv[0];
	std::vector<int> v = {1, 3, 5, 7};
	std::list<double> l = {1.2, 3.4, 5.6, 7.8};
	iterate_over(s);
	iterate_over(v);
	iterate_over(l);
	
	//char hello[] = "Hello!";
	// type of hello: char[7]
// 	int x[] = {1, 4, 5, 7}; // int[4]
// 	
// 	for(int i = 0; i < sizeof(x)/sizeof(*x); i++)
// 	{
// 		std::cout << x[i] << std::endl;
// 	}
// 	
	
	// comp
	// incr
	// add
	// mul
	// deref
}


