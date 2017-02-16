#include <iostream>
#include <cmath>
#include <iomanip>

float carmack_rsqrt(float number, bool snd_iteration)
{
	const float threehalfs = 1.5f;
	const float magic = 0x5f3759df;

	float half_x = number * 0.5;
	float y  = number;
	int32_t i  = *reinterpret_cast<int32_t*>(&number);  // evil floating point bit level hacking
	i  = magic - ( i >> 1 ); 					        // what the fuck? 
	y  = *reinterpret_cast<float*>(&i);
	y  = y * ( threehalfs - ( half_x * y * y ) );       // 1st iteration
    if (snd_iteration)
        y  = y * ( threehalfs - ( half_x * y * y ) );   // 2nd iteration, this can be removed

	return y;
}

float carmack_sqrt(float number, bool snd_iteration)
{
	return 1 / carmack_rsqrt(number, snd_iteration);
}

void print_comparison_results(float number, bool snd_iteration)
{
	float fast_sqrt = carmack_sqrt(number, snd_iteration);
	float stl_sqrt = std::sqrt(number);
    float abs_error = std::fabs(stl_sqrt - fast_sqrt);
    float error_rate = abs_error / stl_sqrt;
    std::cout << "for x = " << std::setw(6) << number << 
            ": carmack sqrt = " << std::setw(12) << fast_sqrt <<
            ", std::sqrt = " << std::setw(12) << stl_sqrt <<
            ", error = " << std::setw(12) << abs_error << "(" << std::setw(12) << error_rate * 100 << "%)" << std::endl;
}

void print_test_results(bool snd_iteration)
{
    const float tests_values[] = { 0.001, 0.01, 0.1, 0.5, 1, 10, 100, 500, 1e10, 1e15, 1e20 };
    for (auto val: tests_values) {
        print_comparison_results(val, snd_iteration);
    }
}

int main(int argc, char** argv)
{
    std::cout << "Carmack's sqrt with one iteration:" << std::endl;
    print_test_results(false);
    std::cout << std::endl << "Carmack's sqrt with two iterations:" << std::endl;
    print_test_results(true);
    return 0;
}
