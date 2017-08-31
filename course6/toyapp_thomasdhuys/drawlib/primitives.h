#pragma once

#include <string>

#include "index.h"

namespace Draw {
namespace Primitives {

class Primitive {
public:
	virtual std::string ToString() = 0;
};

class Point: public Primitive {
public:
	Point(Index& idx0);
	std::string ToString() override;
private:
	Index idx0;
};

class Line: public Primitive {
public:
	Line(Index& idx0, Index& idx1);
	std::string ToString() override;
private:
	Index idx0;
	Index idx1;
};

class Triangle: public Primitive {
public:
	Triangle(Index& idx0, Index& idx1, Index& idx2);
	std::string ToString() override;
private:
	Index idx0;
	Index idx1;
	Index idx2;
};


}}
