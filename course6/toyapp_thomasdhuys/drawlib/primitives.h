#pragma once

#include <string>
#include "index.h"

namespace Draw {
namespace Primitives {

class Primitive {
public:
	virtual std::string ToString() = 0;
};

class Point: private Primitive {
public:
	Point(Index& idx0);
	Point(Index* idx0);
	std::string ToString() override;
private:
	Index* idx0;
};

class Line: private Primitive {
public:
	Line(Index& idx0, Index& idx1);
	Line(Index* idx0, Index* idx1);
	std::string ToString() override;
private:
	Index* idx0;
	Index* idx1;
};

class Triangle: private Primitive {
public:
	Triangle(Index& idx0, Index& idx1, Index& idx2);
	Triangle(Index* idx0, Index* idx1, Index* idx2);
	std::string ToString() override;
private:
	Index* idx0;
	Index* idx1;
	Index* idx2;
};


}}
