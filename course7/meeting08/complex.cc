#include "complex.hh"

#include <cmath>
#include <iostream>
/*
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
*/