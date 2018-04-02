#pragma once

#include "complex.hh"
#include "complex_linked_list.hh"

#include <stack>
#include <string>

class Calculator
{
public:
	void run();

private:
	void parseAndPushComplex(const std::string& line);

	std::pair<Complex, Complex> popPair();

	void add();
	void subtract();
	void multiply();
	void divide();

private:
	std::stack<Complex, ComplexLinkedList> stack;
};
