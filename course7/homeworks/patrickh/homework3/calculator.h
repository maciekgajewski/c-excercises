#include <stack>
#include <string>
#include "complex_linked_list.h"

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
    ComplexLinkedList mStack;
};
