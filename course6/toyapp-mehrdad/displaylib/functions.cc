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
	return {static_cast<int>(x), static_cast<int>(y)};
}

Polygon Rotate(Polygon p, Vector2D origin, Degree angle)
{
	for(auto& v: p)
		v = Rotate(v, origin, angle);
	return p;
}

Polygon ToPolygon(Rect rect)
{
	Polygon p;
	p.push_back(rect.mTopLeft);
	p.push_back(rect.mTopLeft + Vector2D{rect.mSize.mWidth, 0});
	p.push_back(rect.mTopLeft + Vector2D{rect.mSize.mWidth, rect.mSize.mHeight});
	p.push_back(rect.mTopLeft + Vector2D{0, rect.mSize.mHeight});
	return p;
}

Vector2D GetCenter(Rect rect)
{
	return {rect.mTopLeft.mX + rect.mSize.mWidth / 2,
			rect.mTopLeft.mY + rect.mSize.mHeight / 2};
}

}
