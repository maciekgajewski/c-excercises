#include "operation.h"

extern "C" char get_operation_symbol()
{
    return '/';
}

extern "C" void operation(std::stack<Complex>& stack)
{
     if (stack.size() < 2)
         std::cerr << "stack is empty" << std::endl;
     else
     {
         auto& arg2 = stack.top();
         stack.pop();
         auto& arg1 = stack.top();
         stack.pop();
         stack.push(arg1 / arg2);
     }
}
