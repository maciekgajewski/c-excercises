#include "cube.h"

namespace Display {

Cube::Cube(Color color)
{
	mColor = color;
	mVertices[0] = {1, 1, 1};
	mVertices[1] = {1, 1, -1};
	mVertices[2] = {1, -1, 1};
	mVertices[3] = {-1, 1, 1};
	mVertices[4] = {1, -1, -1};
	mVertices[5] = {-1, 1, -1};
	mVertices[6] = {-1, -1, 1};
	mVertices[7] = {-1, -1, -1};
}

Cube Cube::Transform(const Transformation3D& transformation) const
{
	Cube cube(mColor);
	for (int i = 0; i < mVertices.size(); i++)
	{
		cube.mVertices[i] = transformation.Apply(mVertices[i]);
	}
	return cube;
}

void Cube::Draw(Surface3D& surface) const
{
	surface.DrawLine(mVertices[0], mVertices[1], mColor);
	surface.DrawLine(mVertices[0], mVertices[2], mColor);
	surface.DrawLine(mVertices[0], mVertices[3], mColor);
	surface.DrawLine(mVertices[7], mVertices[4], mColor);
	surface.DrawLine(mVertices[7], mVertices[5], mColor);
	surface.DrawLine(mVertices[7], mVertices[6], mColor);
	surface.DrawLine(mVertices[6], mVertices[3], mColor);
	surface.DrawLine(mVertices[6], mVertices[2], mColor);
	surface.DrawLine(mVertices[2], mVertices[4], mColor);
	surface.DrawLine(mVertices[4], mVertices[1], mColor);
	surface.DrawLine(mVertices[1], mVertices[5], mColor);
	surface.DrawLine(mVertices[5], mVertices[3], mColor);
}

}
