#include "complex.h"
#include "complex_stack.h"
#include <iostream>


int main(int argc, char** argv)
{
    ComplexStack stack;

    // this flag is neccessary to allow reading of 'R.R+iI.I' literals which is actually a superfluous feature
    // since this calculator allows for the natural RPN representation, like 'R.RiI.I+'
    bool infix_extempt = false;

    std::cin >> std::ws;
    while(!std::cin.eof()) {
        if (stack.try_read_number(std::cin)) {
            if (stack.top().is_real())
                infix_extempt = true;
        }
        else {
            char command = std::cin.get();
            if ('q' == command)
                break;

            switch(command) {
            case '+':
                if (infix_extempt && 'i' == std::cin.peek())
                    stack.try_read_number(std::cin);
                stack.add();
                break;
            case '-':
                if (infix_extempt && 'i' == std::cin.peek())
                    stack.try_read_number(std::cin);
                stack.substruct();
                break;
            case '*':
                stack.multiply();
                break;
            case '/':
                stack.divide();
                break;
            case 'c':
                stack.clear();
                break;
            case 'f':
                std::cout << stack;
                break;
            case 'p':
                std::cout << stack.top() << std::endl;
                break;
            default:
                std::cerr << "Not implemented: '" << command << "'" << std::endl;
            }

            infix_extempt = false;
        }

        if (std::isspace(std::cin.peek()))
        {
            std::cin >> std::ws;
            infix_extempt = false;
        }
    }
}
