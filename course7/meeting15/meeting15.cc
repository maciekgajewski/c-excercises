#include "foo.hh"
#include "fred.hh"

#include <iostream>
#include <string>
#include <stdexcept>


void bar()
{
	Fred fred("bar");
	throw std::runtime_error("Enough of these Freds!");
}

int main(int argc, char** argv)
{
	Fred mainFred("main");

	try
	{
		foo();
	}
	catch(const std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
}
