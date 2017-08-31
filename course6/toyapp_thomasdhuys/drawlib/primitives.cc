#include "primitives.h"


namespace Draw {
namespace Primitives {

Point::Point(IndexP& idx0): idx0{idx0} {}
std::string Point::ToString()
{
	return "Point(idx0" + idx0->ToString() + ")";
}

Line::Line(IndexP& idx0, IndexP& idx1): idx0{idx0}, idx1{idx1} {}
std::string Line::ToString()
{
	return "Line(idx0" + idx0->ToString() + ",idx1"+idx1->ToString()+")";
}

Triangle::Triangle(IndexP& idx0, IndexP& idx1, IndexP& idx2): idx0{idx0}, idx1{idx1}, idx2{idx2} {}
std::string Triangle::ToString()
{
	return "Triangle(idx0" + idx0->ToString() + ",idx1"+idx1->ToString()+",idx2"+idx2->ToString()+")";
}

}
}
