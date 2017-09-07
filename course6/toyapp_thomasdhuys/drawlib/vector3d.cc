#include "vector3d.h"

namespace Draw {

std::ostream& operator<<(std::ostream& s , const Vector3D& v) { return s << "(" << v.x << "," << v.y << "," << v.z << ")"; }

}
