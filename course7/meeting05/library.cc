#include "library.hh"

int global = 5;

int add(int a, int b)
{
	return a+b + global;
}

double add(double a, double b)
{
	return a+b;
}
