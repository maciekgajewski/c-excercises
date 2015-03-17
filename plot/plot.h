#pragma once


class Point
{
public:
	Point() = default;
	Point(double x, double y): x(x), y(y) {};

	double x=0;
	double y=0;
};


class PlotEngine
{
public:
	virtual ~PlotEngine() = default;

	// Plot range of points
	virtual void plot(Point* begin, Point* end) = 0;

};
