#include "functions.h"

#include <SDL2/SDL.h>

#include <cmath>

namespace Display {

void Delay(int msec)
{
	SDL_Delay(msec);
}

Vector2D Render(Vector3D v)
{
	return {v.mX / v.mZ, v.mY / v.mZ};
}

Vector2D Rotate(Vector2D v, Vector2D origin, Degree angle)
{
	angle = std::fmod(angle, 360.0);
	const double pi = 3.14159265358;
	const Radian r = angle * pi / 180.0;
	const double dX = v.mX - origin.mX;
	const double dY = v.mY - origin.mY;
	double x = (std::cos(r) * dX) - (std::sin(r) * dY) + origin.mX;
	double y = (std::sin(r) * dX) + (std::cos(r) * dY) + origin.mY;
	return {x, y};
}

}
