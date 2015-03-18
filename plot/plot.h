/*
 * Plotting interface.
 *
 *
 * `plot` uses `any_range` abstraction on a container of points.
 *
 *     http://www.boost.org/doc/libs/1_57_0/doc/html/boost_typeerasure.html
 *
 */
#pragma once

#include <boost/range/any_range.hpp>


class Point
{
public:
	Point() = default;
	Point(double x, double y): x(x), y(y) {};

	double x = 0;
	double y = 0;
};


typedef boost::any_range<
    Point
  , boost::forward_traversal_tag
  , Point&
  , std::ptrdiff_t
> points_range;


class PlotEngine
{
public:
	virtual ~PlotEngine() = default;

	// Plot range of points
	virtual void plot(const points_range& points) = 0;

};
