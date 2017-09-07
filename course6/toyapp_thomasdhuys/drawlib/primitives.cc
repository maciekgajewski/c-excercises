#include "primitives.h"


namespace Draw {
namespace Primitives {

std::ostream& Point::StreamWrite(   std::ostream& s) const { return s << *this; };
std::ostream& Line::StreamWrite(    std::ostream& s) const { return s << *this; };
std::ostream& Triangle::StreamWrite(std::ostream& s) const { return s << *this; };

std::ostream& operator<<(std::ostream& s, const Primitive& p) { return p.StreamWrite(s); }
std::ostream& operator<<(std::ostream& s, const Point& p)     { return s << "Point(idx0"    << *p.idx0 << ")"; }
std::ostream& operator<<(std::ostream& s, const Line& p)      { return s << "Line(idx0"     << *p.idx0 << ",idx1" << *p.idx1 << ")"; }
std::ostream& operator<<(std::ostream& s, const Triangle& p)  { return s << "Triangle(idx0" << *p.idx0 << ",idx1" << *p.idx1 << ",idx2" << *p.idx2 << ")"; }

}
}
