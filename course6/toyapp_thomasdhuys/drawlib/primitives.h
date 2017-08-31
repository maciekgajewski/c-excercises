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
	Point(IndexP& idx0);
	std::string ToString() override;
private:
	IndexP idx0;
};

class Line: public Primitive {
public:
	Line(IndexP& idx0, IndexP& idx1);
	std::string ToString() override;
private:
	IndexP idx0;
	IndexP idx1;
};

class Triangle: public Primitive {
public:
	Triangle(IndexP& idx0, IndexP& idx1, IndexP& idx2);
	std::string ToString() override;
private:
	IndexP idx0;
	IndexP idx1;
	IndexP idx2;
};


}}
