#pragma once

#include <iostream>

#include "vertex.h"

namespace Draw {

class RawPrimitive;
using Primitive = std::unique_ptr<RawPrimitive>;

class RawPrimitive {
public:
    virtual Primitive Copy() = 0;
	friend std::ostream& operator<<(std::ostream& s, const RawPrimitive& p);
	friend std::ostream& operator<<(std::ostream& s, const std::unique_ptr<RawPrimitive>& p);
protected:
	virtual std::ostream& StreamWrite(std::ostream& s) const = 0;
};

class Point: public RawPrimitive {
public:
	Point(Vertex& vtx0): vtx0{vtx0} {}
    Primitive Copy() { return std::make_unique<Point>(*this);}
	friend std::ostream& operator<<(std::ostream& s, const Point& p);
protected:
	std::ostream& StreamWrite(std::ostream& s) const;
public:
	Vertex vtx0;
};

class Line: public RawPrimitive {
public:
	Line(Vertex& vtx0, Vertex& vtx1): vtx0{vtx0}, vtx1{vtx1} {}
    Primitive Copy() { return std::make_unique<Line>(*this);}
    friend std::ostream& operator<<(std::ostream& s, const Line& p);
protected:
	std::ostream& StreamWrite(std::ostream& s) const;
public:
	Vertex vtx0;
	Vertex vtx1;
};

class Triangle: public RawPrimitive {
public:
	Triangle(Vertex& vtx0, Vertex& vtx1, Vertex& vtx2): vtx0{vtx0}, vtx1{vtx1}, vtx2{vtx2} {}
    Primitive Copy() { return std::make_unique<Triangle>(*this);}
    friend std::ostream& operator<<(std::ostream& s, const Triangle& p);
protected:
	std::ostream& StreamWrite(std::ostream& s) const;
public:
	Vertex vtx0;
	Vertex vtx1;
	Vertex vtx2;
};

std::ostream& operator<<(std::ostream& s, const Primitive& p);
std::ostream& operator<<(std::ostream& s, const RawPrimitive& p);
std::ostream& operator<<(std::ostream& s, const Point& p);
std::ostream& operator<<(std::ostream& s, const Line& p);
std::ostream& operator<<(std::ostream& s, const Triangle& p);

}
