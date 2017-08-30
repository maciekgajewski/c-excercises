#include "primitives.h"


namespace Draw {
namespace Primitives {

Point::Point(Index& idx0): Point(&idx0) {}
Point::Point(Index* idx0): idx0{idx0} {}
std::string Point::ToString()
{
	return "Point(idx0" + idx0->ToString() + ")";
}

Line::Line(Index& idx0, Index& idx1): Line(&idx0, &idx1) {}
Line::Line(Index* idx0, Index* idx1): idx0{idx0}, idx1{idx1} {}
std::string Line::ToString()
{
	return "Line(idx0" + idx0->ToString() + ",idx1"+idx1->ToString()+")";
}

Triangle::Triangle(Index& idx0, Index& idx1, Index& idx2): Triangle(&idx0, &idx1, &idx2) {}
Triangle::Triangle(Index* idx0, Index* idx1, Index* idx2): idx0{idx0}, idx1{idx1}, idx2{idx2} {}
std::string Triangle::ToString()
{
	return "Triangle(idx0" + idx0->ToString() + ",idx1"+idx1->ToString()+",idx2"+idx2->ToString()+")";
}

}
}
