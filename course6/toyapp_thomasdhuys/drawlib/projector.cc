#include "projector.h"

namespace Draw {

Pixel Projector::Project(Index& idx)
{
	return Pixel{idx->vector.x, idx->vector.y, idx->color};
}

}
