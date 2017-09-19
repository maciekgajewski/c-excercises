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

			auto pushBack3dShift = Vector3D{ 0, 0, 3.5 };
			const auto scaling = 200.0;
			auto centerScreenShift = Vector2D{ surface.GetW() / 2.0, surface.GetH() / 2.0 };

			auto shifted3d = transformed + pushBack3dShift;
			auto zfactor = std::abs(shifted3d.z) < 0.001 ? 0.001 : shifted3d.z;

			return centerScreenShift + Vector2D{shifted3d.x, shifted3d.y } * (scaling / zfactor);
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