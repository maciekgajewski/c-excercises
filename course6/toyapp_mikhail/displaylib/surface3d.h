#pragma once

#include "surface.h"

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

		void DrawLine(Vector3D start, Vector3D end, RGB color)
		{
			surface->DrawLine(Transform(start), Transform(end), color);
		}
	};

	class Cube
	{
		Matrix transformation;
		RGB color;

		void Draw(Surface3D& surface)
		{
			Vector2D edges[] = { Vector2D {-1, -1}, Vector2D{ -1, +1 }, Vector2D{ +1, -1 }, Vector2D{ +1, +1 } };

			for (auto i = 0; i < 4; ++i)
			{
				auto v = edges[i];
				surface.DrawLine(transformation * Vector3D{ v.x, v.y, -1 }, transformation * Vector3D{ v.x, v.y, +1 }, color);
				surface.DrawLine(transformation * Vector3D{ v.x, -1, v.y }, transformation * Vector3D{ v.x, +1, v.y }, color);
				surface.DrawLine(transformation * Vector3D{ -1, v.x, v.y }, transformation * Vector3D{ +1, v.x, v.y }, color);
			}
		}
	};

};