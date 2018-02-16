#include "library.hh"
#include "complex.hh"
#include "rpn_calculator.hh"

int get()
{
	return global + 7;
}

int global_somwhere_else = 45;

class Complex;


int main()
{
	RpnCalculator calc;
	Complex cp(1.1, 2.2);
	return add(get(), global_somwhere_else);
}