#include "shapes3d.h"
#include "functions.h"

namespace Display
{

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
