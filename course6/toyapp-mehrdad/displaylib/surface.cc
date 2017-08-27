#include "surface.h"

#include "functions.h"

#include <cassert>
#include <algorithm>

namespace Display {

Surface::Surface(Size size)
{
	mSurface = SDL_CreateRGBSurface(0, size.mWidth, size.mHeight, 32, 0, 0, 0, 0);
}

Surface::~Surface()
{
	if (mSurface)
		SDL_FreeSurface(mSurface);
}

void Surface::Clear(Color color)
{
	assert(mSurface);

	for(int y = 0; y < mSurface->h; y++)
		for(int x = 0; x < mSurface->w; x++)
			SetPixel({x, y}, color);
}

void Surface::SetPixel(Vector2D point, Color color)
{
	assert(mSurface);

	std::uint32_t* pixelAddr = static_cast<std::uint32_t*>(mSurface->pixels) + (point.mY*mSurface->pitch/4 + point.mX);
	*pixelAddr = color.GetPixelValue();
}

void Surface::DrawLine(Vector2D v1, Vector2D v2, Color color)
{
	// Bresenham's line algorithm
	const bool steep = (fabs(v2.mY - v1.mY) > fabs(v2.mX - v1.mX));
	if(steep)
	{
		std::swap(v1.mX, v1.mY);
		std::swap(v2.mX, v2.mY);
	}

	if(v1.mX > v2.mX)
	{
		std::swap(v1.mX, v2.mX);
		std::swap(v1.mY, v2.mY);
	}

	const float dx = v2.mX - v1.mX;
	const float dy = fabs(v2.mY - v1.mY);

	float error = dx / 2.0f;
	const int ystep = (v1.mY < v2.mY) ? 1 : -1;
	int y = v1.mY;

	const int maxX = v2.mX;

	for(int x=v1.mX; x<maxX; x++)
	{
		if(steep)
		{
			SetPixel({y,x}, color);
		}
		else
		{
			SetPixel({x,y}, color);
		}

		error -= dy;
		if(error < 0)
		{
			y += ystep;
			error += dx;
		}
	}
}

void Surface::DrawRect(Rect rect, Color color)
{
	DrawPolygon(ToPolygon(rect), color);
}

void Surface::DrawRect(Rect rect, Degree rotationAngle, Color color)
{
	Polygon p = ToPolygon(rect);
	Polygon rotated = Rotate(p, GetCenter(rect), rotationAngle);
	DrawPolygon(rotated, color);
}

void Surface::DrawPolygon(const Polygon &p, Color color)
{
	if (p.size() < 3)
		return;//Polygon needs to have at least three edges

	unsigned lastIndex = p.size()-1;
	for (unsigned i = 0; i < lastIndex; ++i)
	{
		DrawLine(p.at(i), p.at(i+1), color);
	}
	DrawLine(p.at(0), p.at(lastIndex), color);
}

void Surface::DrawPolygon(const Polygon &p, Color color, Color cornerColor)
{
	DrawPolygon(p, color);

	for (auto pp: p)
		SetPixel(pp, cornerColor);
}

void Surface::DrawCube(const Polyhedron &p, Color color)
{
	if (p.size() != 8)
		return;

	Polygon p1;
	Polygon p2;
	for (int i = 0; i < 4; ++i)
	{
		p1.push_back(Render(p.at(i)));
		p2.push_back(Render(p.at(i+4)));
	}

	DrawPolygon(p1, color);
	DrawPolygon(p2, color);
	for (int i = 0; i < 4; ++i)
		DrawLine(p1.at(i), p2.at(i), color);
}

}
