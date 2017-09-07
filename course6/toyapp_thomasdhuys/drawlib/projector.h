#pragma once

#include "index.h"
#include "rgb.h"

namespace Draw {

struct Pixel
{
	VCoord x;
	VCoord y;
	RGB color;
};

class Projector {
public:
	static Pixel Project(Index& idx);
private:


};

}
