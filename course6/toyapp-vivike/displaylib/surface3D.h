#pragma once

#include "surface.h"
#include "objects.h"
#include "vector.h"
#include "matrix.h"

#include <SDL2/SDL.h>

#include <cstdint>
#include <vector>

namespace Display {

class Surface3D
// Thank you Mikhail
{
	Surface& surface;
	Vector3D position;
	Vector3D orientation;
	Matrix44 cameraTransform;
	Pixel Transform(Vector3D p)
	{
		Vector3D transformed = cameraTransform * p;
		
		Vector3D pushBack3dShift = Vector3D({ 0, 0, 3.5 });
		const float scaling = 200.0;
		Pixel centerScreenShift = Pixel({ surface.GetW() / 2, surface.GetH() / 2 });

		Vector3D shifted3d = transformed + pushBack3dShift;
		
		float zfactor = std::abs(shifted3d[2]) < 0.001 ? 0.001 : shifted3d[2];
		
		Vector3D scaledLocation = shifted3d * (scaling / zfactor);
		return centerScreenShift + Pixel({int(scaledLocation[0]), int(scaledLocation[1])});
	}
public:
	Surface3D(Surface& s, Vector3D cameraLocation, Vector3D cameraOrientation) : surface(s), position(cameraLocation), orientation(cameraOrientation)
	{
		Matrix44 cameraShift = Matrix44::Translate(position * -1);
		Matrix44 cameraView = Matrix44::Rotate(orientation);
		cameraTransform = cameraShift * cameraView;
	}

	void SetPixel(Vector3D p, Color color);
	void DrawLine(const Vector3D& start, const Vector3D& end, Color color);
	void DrawTriangle(Triangle triangle, Color color);
	void DrawTriangleVector(std::vector<Triangle> triangleVector, Color color);
	
};


}
