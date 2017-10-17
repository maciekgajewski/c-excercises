#pragma once

#include "matrix.h"
#include "vector_common.h"
#include "surface3d.h"
#include "rgb.h"

namespace Display {

	class Cube
	{
	private:
		Matrix transformation;
		RGB color;

	public:
		Cube(Matrix m, RGB color) :transformation(m), color(color) {};
		void Draw(Surface3D& surface)
		{
			Vector2D edges[] = { Vector2D {-1, -1}, Vector2D{ -1, +1 }, Vector2D{ +1, -1 }, Vector2D{ +1, +1 } };

			for (auto i = 0; i < 4; ++i)
			{
				auto v = edges[i];
				surface.DrawLine(transformation * Vector3D{ v.x(), v.y(), -1 }, transformation * Vector3D{ v.x(), v.y(), +1 }, color);
				surface.DrawLine(transformation * Vector3D{ v.x(), -1, v.y() }, transformation * Vector3D{ v.x(), +1, v.y() }, color);
				surface.DrawLine(transformation * Vector3D{ -1, v.x(), v.y() }, transformation * Vector3D{ +1, v.x(), v.y() }, color);
			}
		}
	};

};