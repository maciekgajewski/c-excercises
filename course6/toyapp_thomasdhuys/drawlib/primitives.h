#pragma once

#include <iostream>

#include "index.h"

namespace Draw {
namespace Primitives {

class Primitive {
public:
	friend std::ostream& operator<<(std::ostream& s, const Primitive& p);
protected:
	virtual std::ostream& StreamWrite(std::ostream& s) const = 0;
};

class Point: public Primitive {
public:
	Point(Index& idx0): idx0{idx0} {}
	friend std::ostream& operator<<(std::ostream& s, const Point& p);
protected:
	virtual std::ostream& StreamWrite(std::ostream& s) const;
private:
	Index idx0;
};

class Line: public Primitive {
public:
	Line(Index& idx0, Index& idx1): idx0{idx0}, idx1{idx1} {}
	friend std::ostream& operator<<(std::ostream& s, const Line& p);
protected:
	virtual std::ostream& StreamWrite(std::ostream& s) const;
private:
	Index idx0;
	Index idx1;
};

class Triangle: public Primitive {
public:
	Triangle(Index& idx0, Index& idx1, Index& idx2): idx0{idx0}, idx1{idx1}, idx2{idx2} {}
	friend std::ostream& operator<<(std::ostream& s, const Triangle& p);
protected:
	virtual std::ostream& StreamWrite(std::ostream& s) const;
private:
	Index idx0;
	Index idx1;
	Index idx2;
};

std::ostream& operator<<(std::ostream& s, const Primitive& p);
std::ostream& operator<<(std::ostream& s, const Point& p);
std::ostream& operator<<(std::ostream& s, const Line& p);
std::ostream& operator<<(std::ostream& s, const Triangle& p);

}}
