#include "complex.hh"

#include <stack>

class RpnCalculator
{
public:
	void parse(const std::string& str);

	const Complex& topValue() const { return mStack.top(); }
	bool hasTopValue() const { return !mStack.empty(); }

private:
	void addition();
	void subtraction();
	void multiplication();
	void division();

	std::pair<Complex, Complex> popTwo();

	std::stack<Complex> mStack;
};
