#pragma once

#include <iostream>

struct Complex
{
	Complex() {}

	Complex(double r, double i) : mR(r), mI(i) {}

	bool operator <(const Complex& c) const { return (mR+mI) < (c.mR+c.mI); }

	double mR = 0.0;
	double mI = 0.0;
};

std::ostream& operator<<(std::ostream& s, const Complex& rhs);

