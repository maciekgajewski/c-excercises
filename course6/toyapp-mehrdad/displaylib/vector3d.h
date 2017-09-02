#pragma once

namespace Display {

struct Vector3D
{
	double mX;
	double mY;
	double mZ;
};

Vector3D operator+ (Vector3D v1, Vector3D v2);
Vector3D operator- (Vector3D v1, Vector3D v2);
Vector3D operator+ (Vector3D v1, double scalar);
Vector3D operator- (Vector3D v1, double scalar);
Vector3D operator* (Vector3D v1, double scalar);
Vector3D operator/ (Vector3D v1, double scalar);

}
