#include "calculator.h"

#include <cassert>
#include <stdexcept>

namespace {

  Complex calculate(Complex operand1, Operator op, Complex operand2) {
    switch (op) {
      case Operator::SUM:
        return operand1 + operand2;

      case Operator::SUBTRACTION:
        return operand1 - operand2;

      case Operator::MULTIPLICATION:
        return operand1 * operand2;

      case Operator::DIVISION:
        return operand1 / operand2;

      default:
        assert(false);
        return {0, 0};
    }
  }

}

void RpnCalculator::insert(Complex complex) {
  stack.push(complex);
}

Complex RpnCalculator::insert(Operator op) {
  if (stack.size() < 2)
  {
    throw std::runtime_error("Not enough operands given");
  }

  auto operand2 = stack.top();
  stack.pop();
  auto operand1 = stack.top();
  stack.pop();

  try {
    auto result = calculate(operand1, op, operand2);
    stack.push(result);

    return result;
  }
  catch (const std::runtime_error& e) {
    stack.push(operand1);
    stack.push(operand2);
    throw;
  }
}

const Complex& RpnCalculator::getTop() const {
  return stack.top();
}

bool RpnCalculator::isEmpty() const {
  return stack.empty();
}
