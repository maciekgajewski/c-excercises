#pragma once

#include <stdexcept>
#include <cassert>

enum class Operator
{
  SUM,
  SUBTRACTION,
  MULTIPLICATION,
  DIVISION
};

inline bool isOperator(const std::string& s) {
  return s.size() == 1
      && (s[0] == '+'
       || s[0] == '-'
       || s[0] == '*'
       || s[0] == '/');
}

inline Operator parseOperatorFromString(const std::string& s) {
  assert(isOperator(s));

  switch (s[0]) {
    case '+': return Operator::SUM;
    case '-': return Operator::SUBTRACTION;
    case '*': return Operator::MULTIPLICATION;
    case '/': return Operator::DIVISION;
    default:
      throw std::runtime_error("Unknown operator");
  }
}
