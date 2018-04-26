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

	foo();
}
