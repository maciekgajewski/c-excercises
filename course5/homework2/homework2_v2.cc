#include <iostream>
#include <cmath>

const double EPSILON = 0.001; // 0.1% error

struct Result
{
    double sqrt;
    int depth_of_recursion;
    void* min_stack_ptr;
};

std::ostream& operator<<(std::ostream& s, Result res)
{
    s << "sqrt = " << res.sqrt << ", depth = " << res.depth_of_recursion;
}

Result sqrt(double number, double last_approx)
{
    double x0 = last_approx;
    double y = x0 * x0 - number;
    double ydenom = 2 * x0;

    if (ydenom < EPSILON) { // to avoid dividing by small numbers
        return { x0, 1, &ydenom };
    }

    double x1 = x0 - y / ydenom;

    if (fabs(x1 - x0) < EPSILON * fabs(number)) {
        return { x1, 1, &x1 };
    } else {
        Result res = sqrt(number, x1);
        ++res.depth_of_recursion;
        return std::move(res);
    }
}

int main()
{
    double std_sqrt = std::sqrt(10);
    Result res = sqrt(10, 1);
    int frame_size = static_cast<int>(((size_t)&std_sqrt - (size_t)res.min_stack_ptr) / res.depth_of_recursion);

    std::cout << res << " (" << std_sqrt << ")" << ", frame size " << frame_size << std::endl;
    return 0;
}
