#include "plot.h"
#include "engine_csv.h"

#include <cassert>
#include <iostream>
#include <vector>


void test_plot_csv()
{
	CsvEngine engine(std::cout);

	std::vector<Point> points;
	points.push_back(Point(1, 0));
	points.push_back(Point(2, 0.6931471805599453));
	points.push_back(Point(3, 1.0986122886681098));

    engine.plot(points);

    // TODO: Check output
}


int main()
{
	test_plot_csv();

	std::cout << "All OK" << std::endl;
}
