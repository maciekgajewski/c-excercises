#include "complex.h"
#include "operator.h"
#include "calculator.h"

#include <iostream>
#include <stdexcept>

void insert(RpnCalculator& calculator, Complex complex) {
  calculator.insert(complex);
}

void insert(RpnCalculator& calculator, Operator op) {
  auto result = calculator.insert(op);
  std::cout << "Result so far: " << result << std::endl;
}

void printTopOfStack(const RpnCalculator& calculator) {
  std::cout << "Top of stack: ";

  if (calculator.isEmpty())
    std::cout << "empty";
  else
    std::cout << calculator.getTop();

  std::cout << std::endl;
}

int main(int argc, char** args) {
  std::cout << "Welcome!" << std::endl;
  std::cout << "Type 'q' to quit" << std::endl << std::endl;

  RpnCalculator calculator;

  std::string input;
  while (true) {
    std::getline(std::cin, input);
    if (input == "q")
      break;

    try {
      if (isOperator(input)) {
        insert(calculator, parseOperatorFromString(input));
      }
      else {
        insert(calculator, Complex(input));
      }
    }
    catch (const std::exception& e) {
      std::cout << e.what() << std::endl;
    }

    printTopOfStack(calculator);
  }

  return 0;
}
