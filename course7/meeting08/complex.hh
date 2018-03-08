#pragma once

#include <iostream>
#include <cmath>


template<typename T>
struct Complex
{
	using storage_type = T;

	Complex() {}

	Complex(T r, T i) : mR(r), mI(i) {}

	bool operator <(const Complex& c) const { return (mR+mI) < (c.mR+c.mI); }

	T mR = T();
	T mI = T();
};

template<typename T>
std::ostream& operator<<(std::ostream& s, const Complex<T>& rhs)
{
	s << rhs.mR;
	if (rhs.mI > T())
		s << "+i" << std::abs(rhs.mI);
	else if (rhs.mI < T())
		s << "-i" << std::abs(rhs.mI);

	return s;
}

