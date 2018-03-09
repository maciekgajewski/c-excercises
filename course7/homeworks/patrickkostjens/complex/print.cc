#include "complex.hh"
#include "complex_stack.hh"

#include <iostream>
#include <stack>

extern "C" void execute(ComplexStack& stack)
{
	ComplexStack copy = stack;
	ComplexStack reversed;

	while (!copy.empty())
	{
		reversed.push(copy.pop());
	}

	while (!reversed.empty())
	{
		std::cout << reversed.pop() << std::endl;
	}
}
