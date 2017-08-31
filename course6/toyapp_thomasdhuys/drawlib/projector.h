#pragma once

#include "index.h"
#include "rgb.h"

namespace Draw {

struct Index2D
{
	XCoord x;
	XCoord y;
	RGB color;
};

class Projector {
public:
	static Index2D Project(IndexP& idx);
private:


};

}
