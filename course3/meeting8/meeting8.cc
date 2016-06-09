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


struct S
{
	int f;
	S(int x) : f(x) {}
	S() : f(7) {}
};

int main(int argc, char** argv)
{
	std::cout << "Hello" << std::endl;
	std::array<S, 5> a;
	
	std::vector<char*> v;
	v.reserve(argc);
	for(int i = 0; i < argc; i++)
		v.push_back(argv[i]);
}

