#include "plot.h"
#include "engine_csv.cc"
#include "expr_spirit.cc"

#include <cassert>
#include <iostream>
#include <vector>


void test_parse()
{
	// "x * x"
}


void test_evaluate()
{

}

void test_spirit()
{
	boost::spirit::utree ut;

	assert(expr_parse("2 * 2", ut));

	std::cout << ut << std::endl;

	expr_evaluate(ut);
}


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
	test_parse();
	test_evaluate();
	test_spirit();
	test_plot_csv();

	std::cout << "All OK" << std::endl;
}
