#include "calculator.hh"

#include <regex>

void Calculator::run()
{
	for (std::string line; std::getline(std::cin, line); )
	{
		try
		{
			if (line == "+")
				add();
			else if (line == "-")
				subtract();
			else if (line == "*")
				multiply();
			else if (line == "/")
				divide();
			else
				parseAndPushComplex(line);
		}
		catch(const std::exception& e)
		{
			std::cerr << "Error executing line: " << e.what() << std::endl;
		}
		if (stack.empty())
			std::cout << "empty" << std::endl;
		else
			std::cout << stack.top() << std::endl;
	}
}

void Calculator::parseAndPushComplex(const std::string& line)
{
	static const std::regex regex("^([0-9]+.[0-9]+)(?:\\+i([0-9]+.[0-9]+))?$");

	std::smatch match;
	bool found = std::regex_match(line, match, regex);

	if (!found || match.size() != 3)
		throw std::runtime_error("Cannot parse complex number");

	Complex c(std::stod(match[1].str()));
	if (match[2].matched)
		c.imaginary = std::stod(match[2].str());

	stack.push(c);
}

std::pair<Complex, Complex> Calculator::popPair()
{
	if (stack.size() < 2)
		throw std::runtime_error("Stack does not contain 2 items");
	std::pair<Complex, Complex> pair;
	pair.first = stack.top();
	stack.pop();
	pair.second = stack.top();
	stack.pop();
	return pair;
}

void Calculator::add()
{
	auto pair = popPair();
	stack.push(pair.second + pair.first);
}

void Calculator::subtract()
{
	auto pair = popPair();
	stack.push(pair.second - pair.first);
}

void Calculator::multiply()
{
	auto pair = popPair();
	stack.push(pair.second * pair.first);
}

void Calculator::divide()
{
	auto pair = popPair();
	stack.push(pair.second / pair.first);
}
