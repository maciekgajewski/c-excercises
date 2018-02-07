#pragma once

#include "complex.h"

#include <stack>

enum class Operator
{
  SUM,
  SUBTRACTION,
  MULTIPLICATION,
  DIVISION
};

class RpnCalculator
{
public:
  void insert(Complex);
  Complex insert(Operator);

  const Complex& getTop() const;
  bool isEmpty() const;

private:
  std::stack<Complex> stack;
};
