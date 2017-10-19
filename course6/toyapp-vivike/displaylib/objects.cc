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

Pixel Camera::project2D(Vector3D original)
{
	Pixel newVector({int(original[0]/original[2]), int(original[1]/original[2])});

	return newVector;
}

Rectangle Rectangle::move(Vector3D move)
{
	Rectangle newRectangle({corner1 + move, corner2 + move, corner3 + move, corner4 + move});

	return newRectangle;
}

}
