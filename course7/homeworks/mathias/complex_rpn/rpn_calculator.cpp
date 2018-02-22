#include "rpn_calculator.h"

#include <string>

RpnCalculator::RpnCalculator(std::ostream & output)
	: mOutput(output)
{}

void RpnCalculator::parse(const std::string & str)
{
	if (str.empty())
		return;
	else if (str == "+")
		return addition();
	else if (str == "-")
		return subtraction();
	else if (str == "*")
		return multiplication();
	else if (str == "/")
		return division();
	else if (str == "p")
		return print();
	else if (str == "n")
		return printAndPop();
	else if (str == "f")
		return printStack();
	else if (str == "c")
		return clearStack();
	else if (str == "d")
		return duplicateTop();
	else if (str == "r")
		return reverseTop();

	mStack.emplace_back(str);
}

void RpnCalculator::addition()
{
	auto p = popTwo();
	mStack.emplace_back(p.second + p.first);
}

void RpnCalculator::subtraction()
{
	auto p = popTwo();
	mStack.emplace_back(p.second - p.first);
}

void RpnCalculator::multiplication()
{
	auto p = popTwo();
	mStack.emplace_back(p.second * p.first);
}

void RpnCalculator::division()
{
	auto p = popTwo();
	mStack.emplace_back(p.second / p.first);
}

void RpnCalculator::print() const
{
	requireMinStackSizeOrThrow(1);
	mOutput << mStack.back() << std::endl;
}

void RpnCalculator::printAndPop()
{
	requireMinStackSizeOrThrow(1);
	mOutput << mStack.back() << std::endl;
	mStack.pop_back();
}

void RpnCalculator::printStack() const
{
	auto stack = mStack;
	while (!stack.empty())
	{
		auto value = stack.front();
		stack.pop_front();
		mOutput << value << std::endl;
	}
}

void RpnCalculator::clearStack()
{
	mStack.clear();
}

void RpnCalculator::duplicateTop()
{
	requireMinStackSizeOrThrow(1);
	mStack.push_back(mStack.back());
}

void RpnCalculator::reverseTop()
{
	auto p = popTwo();
	mStack.push_back(p.first);
	mStack.push_back(p.second);
}

std::pair<Complex, Complex> RpnCalculator::popTwo()
{
	requireMinStackSizeOrThrow(2);

	auto a = mStack.back();
	mStack.pop_back();
	auto b = mStack.back();
	mStack.pop_back();
	return { a, b };
}

void RpnCalculator::requireMinStackSizeOrThrow(std::size_t minSize) const
{
	if (mStack.size() < minSize)
		throw std::runtime_error("Not enough values on stack.");
}
