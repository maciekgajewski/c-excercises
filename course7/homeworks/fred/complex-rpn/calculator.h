#pragma once

#include "complex.h"
#include "operator.h"
#include "plugin.h"

#include <functional>
#include <stack>

class RpnCalculator
{
public:
  void insert(Complex complex) { stack.push(complex); };
  Complex calculate(Operator);
  Complex calculate(Plugin);

  const Complex& getTop() const { return stack.top(); };
  bool isEmpty() const { return stack.empty(); };

private:
  Complex consumeAndCalculate(std::function<Complex(Complex, Complex)> operation);

  std::stack<Complex> stack;
};
