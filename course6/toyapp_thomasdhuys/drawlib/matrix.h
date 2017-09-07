#pragma once

#include <array>

#include "index.h"

namespace Draw {

class Matrix4x4 {
public:
	VCoord Get(size_t row, size_t col);
	void   Set(size_t row, size_t col, VCoord value);

	Matrix4x4 operator*(Vector3D v);

private:
	static constexpr size_t COLS = 4;
	static constexpr size_t ROWS = 4;
	std::array< std::array<VCoord,COLS>, ROWS> data;
};

}
