#include "point.h"

// Fun 1
int fun(int x)
{
	return x*2;
}

// Fun 2
int fun(double, char)
{
	return 44;
}

int main(int, char**)
{
	Point p{5, 6};

	return p.length();
}
