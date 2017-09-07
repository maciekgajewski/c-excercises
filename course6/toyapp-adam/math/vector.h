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

	Vector3D operator-() const { return {-x, -y, -z}; }
	Vector3D operator+(const Vector3D& rhs) const { return {x + rhs.x, y + rhs.y, z + rhs.z}; }
	Vector3D operator-(const Vector3D& rhs) const { return {x - rhs.x, y - rhs.y, z - rhs.z}; }
	Vector3D operator*(float scalar) const { return {x * scalar, y * scalar, z * scalar}; }

	Vector3D& operator+=(const Vector3D& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}

	Vector3D& operator-=(const Vector3D& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}

	Vector3D& operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}
};

struct Vector4D
{
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	float w = 0.0f;

	Vector4D() = default;
	Vector4D(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
	Vector4D(Vector3D v, float w) : x(v.x), y(v.y), z(v.z), w(w) {}
	explicit Vector4D(Vector3D v) : x(v.x), y(v.y), z(v.z), w(1.0f) {}

	operator Vector3D() const { return {x, y, z}; }
};

}
