#include "primitives.h"

namespace Draw {
namespace Primitives {

Point::Point(Index& idx): Point(&idx) {}

Point::Point(Index* idx): idx0{idx} {}

}
}
