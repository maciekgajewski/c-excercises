#include <iostream>
#include <cmath>

struct meta_data
{
    int iteration_depth = 0;
    void* stack_begin_void;
    void* stack_end_void;
};

float Newton_sqrt(float number, float x_init, meta_data &metas)
{
    metas.iteration_depth ++;
    float x1 = x_init - (x_init * x_init - number)/(2 * x_init);
    if (metas.iteration_depth == 1)
        metas.stack_begin_void = &x1;
    float diff = std::abs(x1 - x_init);
    if (diff > 0.001)
    {
        return Newton_sqrt(number, x1, metas);
    }
    else
    {
        metas.stack_end_void = &x1;
        return x1;
    }
}

int main(int argc, char** argv)
{
    float number;
    float x_init;
    meta_data metas;
    std::cout << "Please give the number whose sqrt you want to calculate: " << std::endl;
    std::cin >> number;
    std::cout << "Please give your inital guess of the sqrt: " << std::endl;
    std::cin >> x_init;

    float newton_sqrt = Newton_sqrt(number, x_init, metas);
    std::cout << "Newton sqrt is: " << newton_sqrt << std::endl;
    std::cout << "The depth of the iteration is: " << metas.iteration_depth << std::endl;
    char* stack_begin_char = reinterpret_cast<char*>(metas.stack_begin_void);
    char* stack_end_char = reinterpret_cast<char*>(metas.stack_end_void);
    auto stack_frame_size = (stack_begin_char - stack_end_char) / (metas.iteration_depth - 1);

    std::cout << "stack frame size is: " << stack_frame_size << std::endl;
}

//the stack grows from higher to lower.
//the debug compile mode uses bigger stack frame size than the release compile mode.
