#pragma once

#include "surface.h"
#include "matrix.h"
#include "vector3d.h"
#include "triangle.h"

#include <vector>

namespace Display {

	class Surface3D
	{
	private:
		Surface* surface;
		Matrix cameraTransform;
		Vector2D Transform(Vector3D p)
		{
			Vector3D transformed = cameraTransform * p;
			return { transformed.x / transformed.z, transformed.y / transformed.z };// + plus sscaling and shift
		}
	public:
		void SetPixel(Vector3D p, RGB color)
		{
			surface->SetPixel(Transform(p), color);
		}

		void DrawLine(const Vector3D& start, const Vector3D& end, RGB color)
		{
			surface->DrawLine(Transform(start), Transform(end), color);
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