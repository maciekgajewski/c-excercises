#pragma once

#include "complex.hh"
#include "complex_stack.hh"

#include <iostream>
#include <map>
#include <stack>
#include <string>

using plugin = void (*)(ComplexStack&);

class Calculator
{
public:
	void print_status(std::ostream& stream) const;
	void process_line(const std::string& line);
	void add_plugin(const std::string& name, plugin handler);

private:
	ComplexStack stack;
	std::map<std::string, plugin> plugins;

	Complex parse_complex_input(const std::string& line) const;
};
