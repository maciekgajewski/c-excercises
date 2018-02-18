#pragma once

#include "complex.hh"

#include <iostream>
#include <map>
#include <stack>
#include <string>

using plugin = void (*)(std::stack<Complex>&);

class Calculator
{
public:
	void print_status(std::ostream& stream) const;
	void process_line(const std::string& line);
	void add_plugin(const std::string& name, const std::shared_ptr<plugin>& handler);

private:
	std::stack<Complex> stack;
	std::map<std::string, std::shared_ptr<plugin>> plugins;

	Complex parse_complex_input(const std::string& line) const;
};