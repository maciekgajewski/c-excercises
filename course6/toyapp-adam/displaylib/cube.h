#pragma once

#include "vector.h"

namespace Display {

class Cube
{
public:
	Cube(Vector3D center, float size);

	void Draw(Surface3D& surface, Color color) const;
private:
	Vector3D mCenter;
	float mHalfSize;
};

}
