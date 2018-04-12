#include <iostream>
#include <algorithm>
#include <cstring>

bool is_waldo(const char* cstr)
{
	return std::strcmp(cstr, "Waldo") == 0;
}

int main(int argc, char** argv)
{
	int num_waldos = std::count_if(argv, argv+argc, is_waldo);
	std::cout << "Waldos found: " << num_waldos << std::endl;
}


