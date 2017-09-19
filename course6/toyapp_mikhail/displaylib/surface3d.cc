#include "surface3d.h"

namespace Display {

	void Surface3D::Draw(const Triangle& t, RGB color)
	{
		DrawLine(t[0], t[1], color);
		DrawLine(t[0], t[2], color);
		DrawLine(t[1], t[2], color);
	}
}