#include "fred.hh"

void bar();

void foo()
{
	Fred fred("foo");

	bar();
	std::cout << "After calling bar" << std::endl;
}