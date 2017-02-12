#include <iostream>
#include <cmath>

/****
homework02, part 2
Write a recursive function that calculates square root using Newton’s method.
Let the function returns not only the result of the computation, but also some meta data:
- Depth of the recursions
- Enough data that allows you to infer the size of a stack frame of the function. There is several ways of doing it; for instance: you can record the address of some local variable in the function in the first and last call of the function, divided it by (depth-1)

Answer the following:
- which direction does the stack grows?
- what is the impact of compilation mode (debug/release) on the size of the stack frame


Newton's Method, from Wikipedia:
a method for finding successively better approximations to the roots (or zeroes) of a real-valued function.
Given a function f and an initial guess x_n at the root, then a better approximation is:
x_{n+1} = x_{n} - f(x_{n}) / f'(x_{n})

So for square roots:
f(x) = x^2
f'(x) = 2x
x_{n+1} = x_{n} - (x_{n}^2 - x_{n}) / (2 * x_{n})
***/

float newton_sqrt(float input, float result, int num_iters, float** addr_of_last_on_stack)
{
    float arbitrarily_reassigned_input = input;
    std::cout << "Frames remaining  : " << num_iters << std::endl;
    std::cout << "  frame start addr: " << &arbitrarily_reassigned_input << std::endl;
    if (num_iters > 0) {
        result = result - (( std::pow(result, 2) - input) / (2 * result));
        return newton_sqrt(arbitrarily_reassigned_input, result, num_iters - 1, addr_of_last_on_stack);
    }

    float last_arbitrary_local_variable = 0;
    *addr_of_last_on_stack = &last_arbitrary_local_variable;
    return result + last_arbitrary_local_variable;
}

int main(int argc, char** argv)
{
    float input = 16;
    float guess = 90;
    int num_iters = 10;

    float* last_on_stack = nullptr;
    float** addr_of_last_on_stack = &last_on_stack;

    float newton_result = newton_sqrt(input, guess, num_iters, addr_of_last_on_stack);

    float avg_size = (&input - last_on_stack) / (num_iters + 1);

    std::cout << input << ": " << newton_result << " vs " << std::sqrt(input) << std::endl;
    std::cout << "Initial stack addr: " << &input << std::endl;
    std::cout << "Last stack addr   : " << last_on_stack << std::endl;
    std::cout << "Average frame size: " << avg_size << std::endl;
}
