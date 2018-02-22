#pragma once

#include "complex.h"
#include "operator.h"

#include <stack>

class RpnCalculator
{
public:
  void insert(Complex complex) { stack.push(complex); };
  Complex insert(Operator);

  const Complex& getTop() const { return stack.top(); };
  bool isEmpty() const { return stack.empty(); };

private:
  std::stack<Complex> stack;
};
