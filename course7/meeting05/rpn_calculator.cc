#include "rpn_calculator.hh"

#include <string>

void RpnCalculator::parse(const std::string & str)
{
	if (str == "+")
		return addition();
	else if (str == "-")
		return subtraction();
	else if (str == "*")
		return multiplication();
	else if (str == "/")
		return division();

	mStack.emplace(str);
}

void RpnCalculator::addition()
{
	auto p = popTwo();
	mStack.emplace(p.second + p.first);
}

void RpnCalculator::subtraction()
{
	auto p = popTwo();
	mStack.emplace(p.second - p.first);
}

void RpnCalculator::multiplication()
{
	auto p = popTwo();
	mStack.emplace(p.second * p.first);
}

void RpnCalculator::division()
{
	auto p = popTwo();
	mStack.emplace(p.second / p.first);
}

std::pair<Complex, Complex> RpnCalculator::popTwo()
{
	if (mStack.size() < 2)
		throw std::runtime_error("Not enough values on stack.");

	auto a = mStack.top();
	mStack.pop();
	auto b = mStack.top();
	mStack.pop();
	return { a, b };
}
