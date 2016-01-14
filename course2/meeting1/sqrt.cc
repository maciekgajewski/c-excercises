#include <iostream>
#include <cassert>
#include <string>

double do_sqrt(const double val, double current, const double max_d)
{
	double current2 = current*current;
	double d = current2 - val;

	std::cout << "current=" << current << ", d=" << d << std::endl;

	if (d > max_d || d < -max_d)
	{
		double guess = (current + val/current) / 2.0;
		return do_sqrt(val, guess, max_d);
	}
	return current;
}

double sqrt(double val, double prec)
{
	double start = val / 2;
	return do_sqrt(val, start, prec);
}

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cerr << "usage: sqrt value" << std::endl;	
		return 1;
	}
	double val = std::stod(argv[1]);
	double prec = 0.001;
	std::cerr << "Calculating sqrt of " << val << " with precision " << prec << std::endl;
	std::cout << sqrt(val, prec) << std::endl;
}
