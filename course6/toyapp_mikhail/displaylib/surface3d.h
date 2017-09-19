#pragma once

#include "surface.h"
#include "matrix.h"
#include "vector3d.h"
#include "triangle.h"
#include "surface.h"

#include <vector>

namespace Display {

	class Surface3D
	{
	private:
		Surface& surface;
		Matrix cameraTransform;
		Vector2D Transform(Vector3D p)
		{
			auto transformed = cameraTransform * p;

			const auto shift = Vector3D{ 1.5, 1.5, 3.5 };
			auto shited = transformed + shift;

			const auto scaling = 200.0;

			return {
				scaling * shited.x / shited.z,
				scaling * shited.y / shited.z };
		}
	public:
		Surface3D(Surface& s) : surface(s) {}

		void SetPixel(Vector3D p, RGB color)
		{
			surface.SetPixel(Transform(p), color);
		}

		void DrawLine(const Vector3D& start, const Vector3D& end, RGB color)
		{
			surface.DrawLine(Transform(start), Transform(end), color);
		}

		void Draw(const Triangle& t, RGB color);

		void Draw(const std::vector<Triangle>& tt, RGB color)
		{
			for (auto t : tt)
			{
				Draw(t, color);
			}
		}
	};
};