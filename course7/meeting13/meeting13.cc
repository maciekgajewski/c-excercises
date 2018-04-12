#include <iostream>
#include <algorithm>
#include <cstring>

struct is_waldo
{
	bool operator() (const char* cstr) const
	{
		_calls++;
		return std::strcmp(cstr, _search) == 0;
	}
	int& _calls;
	const char* _search;
};

int main(int argc, char** argv)
{
	if (argc < 3)
	{
		std::cerr << "Usage: search WHAT [WHERE...]" << std::endl;
		return 1;
	}

	const char* the_search = argv[1];
	int calls = 0;

	int num_waldos = std::count_if(
		argv+2, argv+argc,
		[&, cc=0](const char* cstr) mutable {
			cc++;
			calls++;
			if (cc < 3)
				return std::strcmp(cstr, the_search) == 0;
			else
				return false;
	});
	
	
	std::cout << "Waldos found: " << num_waldos << std::endl;
	std::cout << "Calls: " << calls << std::endl;
}


