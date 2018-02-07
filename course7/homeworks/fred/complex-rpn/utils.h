#include "complex.h"
#include "calculator.h"

#include <string>
#include <stdexcept>
#include <utility>

Complex parseComplexFromString(const std::string& s) {
  std::string::size_type sz;

  double realPart = std::stod(s, &sz);

  double imaginaryPart = 0.0;
  if (sz < s.size()) {
    if (s[sz] == '+') {
      ++sz;
    }
    else if (s[sz] != '-') {
      throw std::runtime_error("Invalid complex number");
    }

    auto secondPart = s.substr(sz);
    imaginaryPart = std::stod(secondPart, &sz);

    if (sz != secondPart.size() - 1 || secondPart[sz] != 'i') {
      throw std::runtime_error("Invalid complex number");
    }
  }

  return Complex{ realPart, imaginaryPart };
}

std::pair<bool, Complex> tryParseComplexFromString(const std::string& s) {
  try {
    auto result = parseComplexFromString(s);
    return std::make_pair(true, result);
  }
  catch (const std::exception& e) {
    return std::make_pair(false, Complex{0,0});
  }
}

Operator parseOperatorFromString(const std::string& s) {
  if (s.size() != 1) {
    throw std::runtime_error("Invalid operator length");
  }

  switch (s[0]) {
    case '+': return Operator::SUM;
    case '-': return Operator::SUBTRACTION;
    case '*': return Operator::MULTIPLICATION;
    case '/': return Operator::DIVISION;
    default:
      throw std::runtime_error("Unknown operator");
  }
}

std::pair<bool, Operator> tryParseOperatorFromString(const std::string& s) {
  try {
    auto result = parseOperatorFromString(s);
    return std::make_pair(true, result);
  }
  catch (const std::exception& e) {
    return std::make_pair(false, Operator::SUM);
  }
}
