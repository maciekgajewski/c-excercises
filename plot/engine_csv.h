#pragma once

#include "plot.h"

#include <iostream>
#include <iterator>


class CsvEngine: PlotEngine
{
public:

	CsvEngine(const std::ostream& ostream): ostream(ostream) {}

	~CsvEngine() = default;

	virtual void plot(Point* begin, Point* end)
	{
		for (auto p = begin; p != end; p++)
		{
			std::cout << p->x << ", " << p->y << std::endl;
		}

	}

private:
	const std::ostream& ostream;

};
