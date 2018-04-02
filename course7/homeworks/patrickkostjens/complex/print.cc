#include "complex.hh"
#include "complex_stack.hh"

#include <iostream>
#include <stack>

extern "C" void execute(std::stack<Complex, ComplexStack>& stack)
{
	auto copy = stack;
	std::stack<Complex, ComplexStack> reversed;

	while (!copy.empty())
	{
		reversed.push(copy.top());
		copy.pop();
	}

	while (!reversed.empty())
	{
		std::cout << reversed.top() << std::endl;
		reversed.pop();
	}
}
