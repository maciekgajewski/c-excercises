#include "complex.h"
#include "calculator.h"
#include "utils.h"

#include <iostream>
#include <stdexcept>

void insert(RpnCalculator& calculator, Complex complex) {
  calculator.insert(complex);
}

void insert(RpnCalculator& calculator, Operator op) {
  auto result = calculator.insert(op);
  std::cout << "Result so far: " << result << std::endl;
}

int main(int argc, char** args) {
  std::cout << "Welcome!" << std::endl;
  std::cout << "Type 'q' to quit" << std::endl << std::endl;

  RpnCalculator calculator;

  std::string input = "";
  while (true) {
    std::getline(std::cin, input);
    if (input == "q")
      break;

    bool parseFailed = false;

    try {
      // try to parse a number first
      auto parseComplexResult = tryParseComplexFromString(input);
      if (parseComplexResult.first) {
        insert(calculator, parseComplexResult.second);
      }
      else {
        // if failed, try to parse it as an operator
        auto parseOperatorResult = tryParseOperatorFromString(input);
        if (parseOperatorResult.first) {
          insert(calculator, parseOperatorResult.second);
        }
        else {
          parseFailed = true;
        }
      }
    }
    catch (const std::runtime_error& e) {
      std::cout << e.what() << std::endl;
    }

    if (parseFailed) {
        std::cout << "Failed to parse input both as a complex number or operator" << std::endl;
    }

    std::cout << "Top of stack: ";
    if (calculator.isEmpty())
      std::cout << "empty";
    else
      std::cout << calculator.getTop();
    std::cout << std::endl;
  }

  return 0;
}
