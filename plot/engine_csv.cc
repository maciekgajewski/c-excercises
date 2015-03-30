#pragma once

#include "plot.h"

#include <iostream>
#include <iterator>

class CsvEngine: PlotEngine
{
public:

	CsvEngine(const std::ostream& ostream): ostream(ostream) {}

	~CsvEngine() = default;


	virtual void plot(const points_range& points)
	{
        for (auto point : points)
        {
        	std::cout << point.x << "," << point.y << std::endl;
        }
	}

private:
	const std::ostream& ostream;

};
