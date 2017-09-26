#pragma once

#include "matrix.h"
#include "triangle.h"
#include "surface3d.h"
#include "rgb.h"

#include <vector>

namespace Display {

	class Pyramid
	{
	private:
		Matrix _transformation;
		RGB _color;
		std::vector<Triangle> sides;

	public:
		Pyramid(Matrix m, RGB color) :
			_transformation(m),
			_color(color)
		{
			auto base1 = Vector3D{ -0.8, 0.8, 0 };
			auto base2 = Vector3D{ +0.8, 0.8, 0 };
			auto base3 = Vector3D{ 0, 0.4, 0.6 };
			auto top = Vector3D{ 0, -1.2, 0 };

			sides.push_back(Triangle{ base1, base2, base3 });
			sides.push_back(Triangle{ base1, base2, top });
			sides.push_back(Triangle{ base1, top, base3 });
			sides.push_back(Triangle{ top, base2, base3 });
		};

		void Draw(Surface3D& surface)
		{
			surface.Draw(sides, _color);
		}
	};

};