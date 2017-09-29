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

Vector<int, 2> Camera::project2D(Vector<int, 3>& original)
{
	Vector<int, 2> newVector;
	newVector.vec[0] = original.vec[0]/original.vec[2];
	newVector.vec[1] = original.vec[1]/original.vec[2];

	return newVector;
}

Rectangle Rectangle::move(Vector<int, 3>& move)
{
	Rectangle newRectangle;
	newRectangle.corner1 = corner1 + move;
	newRectangle.corner2 = corner2 + move;
	newRectangle.corner3 = corner3 + move;
	newRectangle.corner4 = corner4 + move;

	return newRectangle;
}

}
