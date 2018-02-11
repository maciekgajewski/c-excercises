#include "complex.h"
#include <iostream>
#include <iomanip>
#include <istream>
#include <string>
#include <sstream>
#include <stack>


bool digit_is_comming(std::istream& s)
{
    return '0' <= s.peek() && s.peek() <= '9';
}

bool number_is_comming(std::istream& s)
{
    return '_' == s.peek() || 'i' == s.peek() || digit_is_comming(s);
}



bool try_read_number(std::istream& s, std::stack<Complex>& stack)
{
    if (number_is_comming(std::cin))
    {
        Complex number;
        std::cin >> number;
        stack.push(number);
        return true;
    }
    return false;
}

typedef Complex (*operation)(Complex&, Complex&);

Complex add(Complex& n1, Complex& n2)
{
    return n1 + n2;
}

Complex substruct(Complex& n1, Complex& n2)
{
    return n1 - n2;
}

Complex multiply(Complex& n1, Complex& n2)
{
    return n1 * n2;
}

Complex divide(Complex& n1, Complex& n2)
{
    return n1 / n2;
}

void exec_operation(std::stack<Complex>& stack, operation op)
{
    if (stack.size() < 2)
        std::cerr << "stack is empty" << std::endl;
    else
    {
        auto& arg2 = stack.top();
        stack.pop();
        auto& arg1 = stack.top();
        stack.pop();
        stack.push(op(arg1, arg2));
    }
}

void print_stack(std::stack<Complex>& stack)
{
    std::stack<Complex> tmp_stack;
    while(!stack.empty()) {
        std::cout << stack.top() << std::endl;
        tmp_stack.push(stack.top());
        stack.pop();
    }

    while(!tmp_stack.empty()) {
        stack.push(tmp_stack.top());
        tmp_stack.pop();
    }
}

int main(int argc, char** argv)
{
    std::stack<Complex> stack;

    // this flag is neccessary to allow reading of 'R.R+iI.I' literals which is actually a superfluous feature
    // since this calculator allows for the natural RPN representation, like 'R.RiI.I+'
    bool inflix_extempt = false;

    std::cin >> std::ws;
    while(!std::cin.eof()) {
        if (try_read_number(std::cin, stack)) {
            if (stack.top().is_real())
                inflix_extempt = true;
        }
        else {
            char command = std::cin.get();
            if ('q' == command)
                break;

            switch(command) {
            case '+':
                if (inflix_extempt)
                    try_read_number(std::cin, stack);
                exec_operation(stack, add);
                break;
            case '-':
                if (inflix_extempt)
                    try_read_number(std::cin, stack);
                exec_operation(stack, substruct);
                break;
            case '*':
                exec_operation(stack, multiply);
                break;
            case '/':
                exec_operation(stack, divide);
                break;
            case 'c':
                stack = std::stack<Complex>();
                break;
            case 'f':
                print_stack(stack);
                break;
            case 'p':
                std::cout << stack.top() << std::endl;
                break;
            default:
                std::cerr << "Not implemented: '" << command << "'" << std::endl;
            }

            inflix_extempt = false;
        }

        if (std::isspace(std::cin.peek()))
        {
            std::cin >> std::ws;
            inflix_extempt = false;
        }
    }
}
