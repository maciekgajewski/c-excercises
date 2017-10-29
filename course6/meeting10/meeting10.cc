#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>


struct Args
{
	int mArgc;
	char** mArgv;

	char** begin() const { return mArgv; }
	char** end() const { return mArgv + mArgc; }
};

int main(int argc, char** argv)
{
	Args arguments{argc, argv};

	for(auto a : arguments)
		std::cout << a << std::endl;
}
 