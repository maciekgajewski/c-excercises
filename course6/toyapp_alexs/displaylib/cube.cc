#include "surface.h"
#include "cube.h"
#include "vector3d.h"
#include "transformation3d.h"

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
	surface.SetPixel(mVertices[0], this->mColor);
	surface.SetPixel(mVertices[1], this->mColor);
	surface.SetPixel(mVertices[2], this->mColor);
	surface.SetPixel(mVertices[3], this->mColor);
	surface.SetPixel(mVertices[4], this->mColor);
	surface.SetPixel(mVertices[5], this->mColor);
	surface.SetPixel(mVertices[6], this->mColor);
	surface.SetPixel(mVertices[7], this->mColor);
}

}
