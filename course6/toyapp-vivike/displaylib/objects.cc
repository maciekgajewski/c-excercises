#include "objects.h"

#include <SDL2/SDL.h>

namespace Display {

void Color::Redder(int amount)
{
	if(R + amount <= 255)
	{
		R = R + amount;
	}
};

void Vector2D::move(int xmove, int ymove)
{
	x = x + xmove;
	y = y + ymove;
};

Vector2D Vector3D::project2D()
{
	Vector2D newVector;
	newVector.x = x/z;
	newVector.y = y/z;

	return newVector;
}

}
