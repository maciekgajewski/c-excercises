#include "foo.hh"
#include "fred.hh"

#include <iostream>
#include <string>
#include <stdexcept>


void bar()
{
	Fred fred("bar");
	throw Fred("boo");
	std::cout << "After throw" << std::endl;
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
	/**/
	catch(const std::exception* eptr)
	{
		std::cout << "C# Error: " << eptr->what() << std::endl;
	}
	catch(...)
	{
		std::cout << "Weird exception!" << std::endl;
		throw;
	}/**/
}













/*
template<typename Fun, typename... Params>
void logAndCall(Fun f, Params&&... p)
{
	log("Before calling");
	try{
		f(std::forward<Params>(p)...);
		log("after calling");
	}
	catch(...)
	{
		log("exception thrown");
		throw;
	}
}
*/