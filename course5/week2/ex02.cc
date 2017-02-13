#include <iostream>
#include <cmath>
#include <chrono>

// ARS - 20170213
// Cormacks algo from https://en.wikipedia.org/wiki/Fast_inverse_square_root
// With slight modifications to C++-ifyusing dynamic c

float Q_sqrt(float);

float Q_sqrt( float number )
{
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y  = number;

	// ARS: Original was: i  = * ( long * ) &y;
	i  = * reinterpret_cast<long *> (&y);                       // evil floating point bit level hacking
	i  = 0x5f3759df - ( i >> 1 );               // what the fuck? 
	// ARS. Original was: y  = * ( float * ) &i;
	y  = * reinterpret_cast<float *> (&i);
	y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration

	return number*y;
}

void TimeIt(int max_nr)
{
    // OBSERVATIONS: Hack seems to be much slower than std:sqrt???
    // Iterating over e.g. 1E06 numbers, gives 50ms for Cormacks, vs 7 for std::sqrt. Dos the latter use native assembly sqrt??

    float dummy_sum_Qsqrt = 0.0;

    //time Q_sqrt function first
    auto t1 = std::chrono::high_resolution_clock::now();
    for (auto i=0; i < max_nr; i++)
    {
	dummy_sum_Qsqrt += Q_sqrt(i);
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    auto res =  std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();

    //time std::sqrt function first
    auto dummy_sum_sqrt = 0.0;
    for (auto i=0; i < max_nr; i++)
    {
	dummy_sum_sqrt += std::sqrt(i);
    }
    auto t3 = std::chrono::high_resolution_clock::now();
    auto res2 =  std::chrono::duration_cast<std::chrono::milliseconds>(t3-t2).count();
   
    std::cout << "dummy sum for Q   SQRT= "<< dummy_sum_Qsqrt  << " calculated in "<< res << "ms"<< std::endl;
    std::cout << "dummy sum for STD SQRT= "<< dummy_sum_sqrt  << " calculated in "<< res2 << "ms"<< std::endl;

}

void DiffIt(int max_nr)
{
    // OBSERVATION: seems to be quiet close to actual number. Higher than 99.8% accuracy of the actual sqrt

    float qsqrt, stdsqrt; 
    for (auto i=0; i < max_nr; i++)
    {
	qsqrt = Q_sqrt(i);
	stdsqrt = std::sqrt(i);
	std::cout << "for "<< i << ",the diff of "<< qsqrt << "and "<< stdsqrt <<  "= " << 100.0* qsqrt/stdsqrt << std::endl;
    }

}



int main(int argc, char** argv)
{
    if (argc != 2)
    {
		std::cout << "Usage: %s <max_number>" << std::endl;
		exit(0);
    }
    auto max_nr = std::atoi(argv[1]);
    TimeIt(max_nr);
    DiffIt(max_nr);
	
    return 0;
}

