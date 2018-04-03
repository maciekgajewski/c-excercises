#include "../complex.h"

extern "C" Complex average(Complex c1, Complex c2)
{
  return Complex((c1.real + c2.real) / 2.0, (c1.imaginary + c2.imaginary) / 2.0);
}
