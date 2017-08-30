#include "primitives.h"

namespace Draw {
namespace Primitives {

Point::Point(Index& idx0): Point(&idx0) {}
Point::Point(Index* idx0): idx0{idx0} {}

Line::Line(Index& idx0, Index& idx1): Line(&idx0, &idx1) {}
Line::Line(Index* idx0, Index* idx1): idx0{idx0}, idx1{idx1} {}

Triangle::Triangle(Index& idx0, Index& idx1, Index& idx2): Triangle(&idx0, &idx1, &idx2) {}
Triangle::Triangle(Index* idx0, Index* idx1, Index* idx2): idx0{idx0}, idx1{idx1}, idx2{idx2} {}

}
}
