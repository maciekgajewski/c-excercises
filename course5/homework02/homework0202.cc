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

float newton_sqrt(float input, float result, int num_iters)
{
    if (num_iters > 0) {
        result = result - (( result * result - input) / (2 * result));
        return newton_sqrt(input, result, num_iters - 1);
    }
    return result;
}

int main(int argc, char** argv)
{
    float input = 16;
    float guess = 90;
    int num_iters = 10;

    float newton_result = newton_sqrt(input, guess, num_iters);
    std::cout << input << ": " << newton_result << " vs " << std::sqrt(input) << std::endl;
}