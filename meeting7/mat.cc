#include "mat.h"

double Calculator::square(double x)
{
    return x*x;
}

double Calculator::max(double a, double b)
{
    if (a > b)
        return a;
    else
        return b;
}
