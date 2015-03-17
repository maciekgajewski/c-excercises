#include "plot.h"
#include "engine_csv.h"

#include <cassert>
#include <iostream>
#include <vector>


void test_plot_csv()
{
	CsvEngine engine(std::cout);
	Point* a = new Point[3];
	a[0] = Point(0.0, 0.0);
	a[1] = Point(1.0, 1.0);
	a[2] = Point(2.0, 2.0);

	engine.plot(a, a+3);
}


int main()
{
	test_plot_csv();

	std::cout << "All OK" << std::endl;
}
