#include "complex.hh"

#include <cmath>
#include <iostream>

std::ostream& operator<<(std::ostream& s, const Complex& rhs)
{
	s << rhs.mR;
	if (rhs.mI > 0.0)
		s << "+i" << std::fabs(rhs.mI);
	else if (rhs.mI < 0.0)
		s << "-i" << std::fabs(rhs.mI);

	return s;
}
