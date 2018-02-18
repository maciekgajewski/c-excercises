#include "complex.hh"

#include <iostream>
#include <stack>

extern "C" void execute(std::stack<Complex>& stack)
{
	std::stack<Complex> copy = stack;
	std::stack<Complex> reversed;

	while (copy.size() > 0)
	{
		reversed.push(copy.top());
		copy.pop();
	}

	while (reversed.size() > 0)
	{
		Complex next = reversed.top();
		reversed.pop();
		std::cout << next << std::endl;
	}
}
