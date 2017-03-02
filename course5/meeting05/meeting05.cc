#include <iostream>
#include <string>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <thread>

struct Length
{
	Length(double m) :mMeters(m) {}
	
	double ToMeters() const { return mMeters; }
	double ToInches() const { return mMeters * 39.37; }
	
	Length operator-(const Length& o) const
	{
		return Length(mMeters - o.mMeters);
	}
	
private:
	double mMeters = 0.0;
};

std::ostream& operator<<(std::ostream& s, const Length& l)
{
	s << l.ToMeters() << "m";
	return s;
}

Length operator "" _m(long double meters){ return Length(meters);}
Length operator "" _cm(long double c){ return Length(c/100.0);}
Length operator "" _cm(unsigned long long c){ return Length(c/100.0);}

using namespace std::literals;

int main(int /*argc*/, char** /*argv*/)
{
	Length l(2);
	
	std::cout << "Maciek's height: " << l << std::endl;
	std::this_thread::sleep_for(3min);
	std::cout <<"Fei's height: " << l - 28_cm << std::endl;
	
	
}

