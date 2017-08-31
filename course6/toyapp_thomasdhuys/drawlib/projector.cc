#include "projector.h"

namespace Draw {

Pixel Projector::Project(Index& idx)
{
	return Pixel{idx->x, idx->y, idx->color};
}

}
