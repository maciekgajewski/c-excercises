#pragma once

#include "vertex.h"
#include "color.h"

namespace Draw {

struct Pixel
{
	VCoord x;
	VCoord y;
	Color color;
};

class Projector {
public:
	static Pixel Project(Index& idx);
private:


};

}
