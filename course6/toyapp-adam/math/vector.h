#pragma once

namespace Math {

struct Vector2D
{
	float x = 0.0f;
	float y = 0.0f;
};

struct Vector3D
{
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

	Vector3D operator-() const;
	Vector3D operator+(const Vector3D& rhs) const;
	Vector3D operator-(const Vector3D& rhs) const;
	Vector3D operator*(float scalar) const;
	Vector3D& operator+=(const Vector3D& rhs);
	Vector3D& operator-=(const Vector3D& rhs);
	Vector3D& operator*=(float scalar);
};

struct Vector4D
{
	float x;
	float y;
	float z;
	float w;

	Vector4D(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
	Vector4D(Vector3D v, float w) : x(v.x), y(v.y), z(v.z), w(w) {}
	explicit Vector4D(Vector3D v) : x(v.x), y(v.y), z(v.z), w(1.0f) {}

	operator Vector3D() const { return {x, y, z}; }
};

}
