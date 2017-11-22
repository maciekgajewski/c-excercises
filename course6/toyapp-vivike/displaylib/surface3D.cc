#include "surface3D.h"

namespace Display {

	void Surface3D::Rotate(Vector3D rotation)
	{
		Matrix44 cameraShift = Matrix44::Translate(position * -1);
		Matrix44 oldCameraView = Matrix44::Rotate(orientation);
		Matrix44 additionalRotation = Matrix44::Rotate(rotation);
		cameraTransform = cameraShift * additionalRotation * oldCameraView;
	}

	Matrix44 Surface3D::createInverseMatrix()
	{
		return Matrix44::Rotate(-orientation) * Matrix44::Translate(-position);
	}

	void Surface3D::SetPixel(Vector3D p, Color color)
	{
		surface.SetPixel(Transform(p), color);
	}

	void Surface3D::DrawLine(const Vector3D& start, const Vector3D& end, Color color)
	{
		surface.DrawLine(Transform(start), Transform(end), color);
	}

	void Surface3D::DrawTriangle(Triangle triangle, Color color)
	{
		for(auto line : triangle.edges())
		{
			DrawLine(line[0], line[1], color);
		}
	}

	void Surface3D::DrawTriangleVector(std::vector<Triangle> triangleVector, Color color)
	{
		for(auto tri : triangleVector)
		{
			DrawTriangle(tri, color);
		}
		
	}

	void Surface3D::DrawMesh(const Mesh& mesh, const Matrix44& view)
	{
		auto modelView = view * mesh.transform.CreateMatrix();
		for (auto& triangle : mesh.triangles)
		{
			Triangle viewTransformedTriangle = {
				modelView * triangle[0],
				modelView * triangle[1],
				modelView * triangle[2]
			};

			DrawTriangle(viewTransformedTriangle, mesh.fillColor);
			DrawLine(viewTransformedTriangle[0], viewTransformedTriangle[1], mesh.edgeColor);
			DrawLine(viewTransformedTriangle[0], viewTransformedTriangle[2], mesh.edgeColor);
			DrawLine(viewTransformedTriangle[1], viewTransformedTriangle[2], mesh.edgeColor);
		}
	}

}