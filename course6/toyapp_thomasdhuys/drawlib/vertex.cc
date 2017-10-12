#include "vertex.h"
#include "color.h"

namespace Draw {

std::ostream& operator<<(std::ostream& s, const Vertex& v) { return s << v.vector << " " << v.color; }

}
