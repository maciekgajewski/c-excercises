#pragma once

#include "index.h"

namespace Draw {
namespace Primitives {

class Point {
public:
	Point(Index& idx0);
	Point(Index* idx0);
private:
	Index* idx0;
};

class Line {
public:
	Line(Index& idx0, Index& idx1);
	Line(Index* idx0, Index* idx1);
private:
	Index* idx0;
	Index* idx1;
};

class Triangle {
public:
	Triangle(Index& idx0, Index& idx1, Index& idx2);
	Triangle(Index* idx0, Index* idx1, Index* idx2);
private:
	Index* idx0;
	Index* idx1;
	Index* idx2;
};


}}
