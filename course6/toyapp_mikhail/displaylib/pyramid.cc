#include "pyramid.h"

namespace Display {

Pyramid::Pyramid(Matrix m, RGB color) :
	mTransformation(m),
	mColor(color)
{
	auto base1 = Vector3D{ -0.8, 0.8, 0 };
	auto base2 = Vector3D{ +0.8, 0.8, 0 };
	auto base3 = Vector3D{ 0, 0.4, 0.6 };
	auto top = Vector3D{ 0, -1.2, 0 };

	mSides.push_back(Triangle{ base1, base2, base3 });
	mSides.push_back(Triangle{ base1, base2, top });
	mSides.push_back(Triangle{ base1, top, base3 });
	mSides.push_back(Triangle{ top, base2, base3 });
};

}
