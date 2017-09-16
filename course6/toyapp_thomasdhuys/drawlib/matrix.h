#pragma once

#include <array>

#include "vertex.h"

namespace Draw {

namespace {
	static constexpr size_t COLS = 4;
	static constexpr size_t ROWS = 4;
}

using RowType = std::array<VCoord, COLS>;

class Matrix4x4 {
private:
	std::array< RowType, ROWS> data;

public:
	static Matrix4x4 Zero();
	static Matrix4x4 Identity();
	static Matrix4x4 Translation(Vector3D position);
	static Matrix4x4 Rotation(Vector3D yawPitchRoll);
	static Matrix4x4 Scale(float factor);
	static Matrix4x4 Perspective(float fieldOfViewDegrees, float aspectRatio);

	Matrix4x4();
	Vector3D operator*(Vector3D& rhs);
	Matrix4x4 operator*(Matrix4x4& rhs);
	RowType& operator[](std::size_t index) {return data[index];}
	const RowType& operator[](std::size_t index) const {return data[index];}

};

}
