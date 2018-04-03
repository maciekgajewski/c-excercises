#include "calculator.h"

#include <cassert>
#include <stdexcept>

Complex RpnCalculator::calculate(Operator op)
{
  return consumeAndCalculate([op](Complex operand1, Complex operand2) {
    switch (op)
    {
      case Operator::SUM:
        return operand1 + operand2;

      case Operator::SUBTRACTION:
        return operand1 - operand2;

      case Operator::MULTIPLICATION:
        return operand1 * operand2;

      case Operator::DIVISION:
        return operand1 / operand2;
    }
  });
}

Complex RpnCalculator::calculate(Plugin plugin)
{
  return consumeAndCalculate(plugin);
}

Complex RpnCalculator::consumeAndCalculate(std::function<Complex(Complex, Complex)> operation)
{
  if (stack.size() < 2)
  {
    throw std::runtime_error("Not enough operands given");
  }

  auto operand2 = stack.top();
  stack.pop();
  auto operand1 = stack.top();
  stack.pop();

  try
  {
    auto result = operation(operand1, operand2);
    stack.push(result);

    return result;
  }
  catch (const std::runtime_error& e)
  {
    stack.push(operand1);
    stack.push(operand2);
    throw;
  }
}
