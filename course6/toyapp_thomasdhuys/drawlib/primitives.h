#pragma once

#include <iostream>

#include "vertex.h"

namespace Draw {


class RawPrimitive {
public:
	friend std::ostream& operator<<(std::ostream& s, const RawPrimitive& p);
	friend std::ostream& operator<<(std::ostream& s, const std::unique_ptr<RawPrimitive>& p);
protected:
	virtual std::ostream& StreamWrite(std::ostream& s) const = 0;
};

using Primitive = std::unique_ptr<RawPrimitive>;

class Point: public RawPrimitive {
public:
	Point(Index& idx0): idx0{idx0} {}
	friend std::ostream& operator<<(std::ostream& s, const Point& p);
protected:
	virtual std::ostream& StreamWrite(std::ostream& s) const;
public:
	Index idx0;
};

class Line: public RawPrimitive {
public:
	Line(Index& idx0, Index& idx1): idx0{idx0}, idx1{idx1} {}
	friend std::ostream& operator<<(std::ostream& s, const Line& p);
protected:
	virtual std::ostream& StreamWrite(std::ostream& s) const;
public:
	Index idx0;
	Index idx1;
};

class Triangle: public RawPrimitive {
public:
	Triangle(Index& idx0, Index& idx1, Index& idx2): idx0{idx0}, idx1{idx1}, idx2{idx2} {}
	friend std::ostream& operator<<(std::ostream& s, const Triangle& p);
protected:
	virtual std::ostream& StreamWrite(std::ostream& s) const;
public:
	Index idx0;
	Index idx1;
	Index idx2;
};

std::ostream& operator<<(std::ostream& s, const Primitive& p);
std::ostream& operator<<(std::ostream& s, const RawPrimitive& p);
std::ostream& operator<<(std::ostream& s, const Point& p);
std::ostream& operator<<(std::ostream& s, const Line& p);
std::ostream& operator<<(std::ostream& s, const Triangle& p);

}
