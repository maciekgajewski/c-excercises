#include "primitives.h"


namespace Draw {

std::ostream& Point::StreamWrite(   std::ostream& s) const { return s << *this; };
std::ostream& Line::StreamWrite(    std::ostream& s) const { return s << *this; };
std::ostream& Triangle::StreamWrite(std::ostream& s) const { return s << *this; };

std::ostream& operator<<(std::ostream& s, const Primitive& p) { return p->StreamWrite(s); }
std::ostream& operator<<(std::ostream& s, const RawPrimitive& p) { return p.StreamWrite(s); }
std::ostream& operator<<(std::ostream& s, const Point& p)     { return s << "Point(vtx0"    << p.vtx0 << ")"; }
std::ostream& operator<<(std::ostream& s, const Line& p)      { return s << "Line(vtx0"     << p.vtx0 << ",vtx1" << p.vtx1 << ")"; }
std::ostream& operator<<(std::ostream& s, const Triangle& p)  { return s << "Triangle(vtx0" << p.vtx0 << ",vtx1" << p.vtx1 << ",vtx2" << p.vtx2 << ")"; }

}
