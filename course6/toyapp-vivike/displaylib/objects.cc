#include "objects.h"

#include <SDL2/SDL.h>

namespace Display {

void Color::redder(int amount)
{
	if(R + amount <= 255)
	{
		R = R + amount;
	}
};

Pixel Camera::project2D(Vector3D& original)
{
	Pixel newVector;
	newVector.vec[0] = int(original.vec[0]/original.vec[2]);
	newVector.vec[1] = int(original.vec[1]/original.vec[2]);

	return newVector;
}

Rectangle Rectangle::move(Vector3D& move)
{
	Rectangle newRectangle;
	newRectangle.corner1 = corner1 + move;
	newRectangle.corner2 = corner2 + move;
	newRectangle.corner3 = corner3 + move;
	newRectangle.corner4 = corner4 + move;

	return newRectangle;
}

}
