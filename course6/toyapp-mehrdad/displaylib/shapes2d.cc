#include "shapes2d.h"
#include "functions.h"

namespace Display
{

Rect::Rect(Vector2D tl, Size size)
{
	mVertices[0] = tl;
	mVertices[1] = {tl.mX + size.mWidth, tl.mY};
	mVertices[2] = {tl.mX + size.mWidth, tl.mY + size.mHeight};
	mVertices[3] = {tl.mX , tl.mY + size.mHeight};
}

void Rect::Draw(Surface &surface, Color color)
{
	unsigned lastIndex = 3;
	for (unsigned i = 0; i < lastIndex; ++i)
	{
		surface.DrawLine(mVertices.at(i).ToPixel(), mVertices.at(i+1).ToPixel(), color);
	}
	surface.DrawLine(mVertices.at(0).ToPixel(), mVertices.at(lastIndex).ToPixel(), color);
}

void Rect::Rotate(Degree angle)
{
	auto halfWidth = (mVertices[1].mX - mVertices[0].mX) / 2;
	Vector2D center = {mVertices[0].mX + halfWidth,
					   mVertices[0].mY + halfWidth};
	for(auto& v: mVertices)
		v = Display::Rotate(v, center, angle);
}

}
