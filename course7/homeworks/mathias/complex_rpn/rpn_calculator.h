#pragma once

#include "complex.h"

#include <deque>

class RpnCalculator
{
public:
	RpnCalculator(std::ostream& output);
	void parse(const std::string& str);

private:
	void addition();
	void subtraction();
	void multiplication();
	void division();

	void print() const;
	void printAndPop();
	void printStack() const;

	void clearStack();
	void duplicateTop();
	void reverseTop();

	std::pair<Complex, Complex> popTwo();

	void requireMinStackSizeOrThrow(std::size_t minSize) const;

	std::deque<Complex> mStack;
	std::ostream& mOutput;
};
