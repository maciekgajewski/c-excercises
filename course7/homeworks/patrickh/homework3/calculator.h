#include <stack>
#include <string>
#include "complex.h"

class Calculator
{
public:
    void parse(const std::string& input);
    void add();
    void subtract();
    void multiply();
    void divide();
    void printValue();
private:
    std::stack<Complex> mStack;
};
