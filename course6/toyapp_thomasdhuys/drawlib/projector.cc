#include "projector.h"

namespace Draw {

Index2D Projector::Project(IndexP& idx)
{
	return Index2D{idx->x, idx->y, idx->color};
}

}
