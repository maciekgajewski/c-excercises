#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <string>
#include <cstring>
#include <cctype>

bool less_than_case_insensitive(const char* a, const char* b)
{
	while(*a != '\0' && std::tolower(*a) == std::tolower(*b))
	{
		++a; ++b;
	}
	return std::tolower(*a) < std::tolower(*b);
}

template<typename Comparison>
void sort_params(char** first, char** last, Comparison comp)
{
	std::vector<const char*> params;
	params.reserve(std::distance(first, last));
	std::copy(first, last, std::back_inserter(params));

	std::sort(params.begin(), params.end(), comp);

	std::copy(params.begin(), params.end(), std::ostream_iterator<const char*>(std::cout, " "));
	std::cout << std::endl;
}

int main(int argc, char** argv)
{
	if (std::strcmp(argv[1], "-i") == 0)
		sort_params(argv+2, argv+argc, less_than_case_insensitive);
	else
		sort_params(argv+1, argv+argc, [](const char* a, const char* b) { return std::strcmp(a, b) < 0;});
}
