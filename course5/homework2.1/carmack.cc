#include <cmath>
#include <iostream>
#include <cstdlib>

const float ONE_HALF = 0.5;
const float THREE_HALFS = 1.5;
const int FAST_INVERSE_SQRT_MAGIC = 0x5f3759df;

float fastInvSqrt(float input)
{
        unsigned long temporaryIntegerForm;
        temporaryIntegerForm = *reinterpret_cast<unsigned long *>(&input);
        temporaryIntegerForm = FAST_INVERSE_SQRT_MAGIC - (temporaryIntegerForm >> 1);
        auto approximateResult = *reinterpret_cast<float *>(&temporaryIntegerForm);
        approximateResult = approximateResult * (THREE_HALFS - (ONE_HALF * input * approximateResult * approximateResult));
        return approximateResult;
}

float fastSqrt(float input)
{
        return 1 / fastInvSqrt(input);
}

int main(int argc, char** argv)
{
        for (auto i = 1; i < argc; i++)
        {
                auto input = std::atof(argv[i]);
                auto fastResult = fastSqrt(input);
                auto stdResult = std::sqrt(input);
                auto error = std::abs(fastResult - stdResult) / stdResult;
                std::cout << "fastSqrt(" << argv[i] << ")=" << fastResult << "; std::sqrt(" << argv[i] << ")=" << stdResult << "; error=" << error * 100. << "%" << std::endl;
        }
}
