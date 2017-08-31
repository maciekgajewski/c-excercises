#include "shapes.h"
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

Cube::Cube()
{
	Vector3D center{0, 0, 1.5};
	int width = 1;
	double half = width * 0.5;

	mVertices[0] = {center.mX - half, center.mY - half, center.mZ - half};
	mVertices[1] = {center.mX + half, center.mY - half, center.mZ - half};
	mVertices[2] = {center.mX + half, center.mY + half, center.mZ - half};
	mVertices[3] = {center.mX - half, center.mY + half, center.mZ - half};
	mVertices[4] = {center.mX - half, center.mY - half, center.mZ + half};
	mVertices[5] = {center.mX + half, center.mY - half, center.mZ + half};
	mVertices[6] = {center.mX + half, center.mY + half, center.mZ + half};
	mVertices[7] = {center.mX - half, center.mY + half, center.mZ + half};
}

void Cube::Draw(Surface &surface, Color color) const
{
	Size surfaceSize = surface.GetSize();
	Pixel halfScreen{surfaceSize.mWidth / 2, surfaceSize.mHeight / 2};

	for (auto p: mVertices)
	{
		Vector2D point = Render(p);
		point.mX = point.mX * halfScreen.mX + halfScreen.mX;
		point.mY = point.mY * halfScreen.mY + halfScreen.mY;
		surface.SetPixel(point.ToPixel(), color);
	}
}

}
