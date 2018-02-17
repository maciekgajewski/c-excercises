#pragma once

#include "complex.hh"

#include <iostream>
#include <stack>
#include <string>

class Calculator
{
public:
	void print_status(std::ostream& stream) const;
	void process_line(const std::string& line);

private:
	std::stack<Complex> stack;

	Complex parse_complex_input(const std::string& line) const;
};