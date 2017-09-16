#pragma once

#include <array>

#include "vertex.h"

namespace Draw {

class Matrix4x4 {
private:
	static constexpr size_t COLS = 4;
	static constexpr size_t ROWS = 4;
	std::array< std::array<VCoord,COLS>, ROWS> data;

public:
	VCoord Get(size_t row, size_t col);
	void   Set(size_t row, size_t col, VCoord value);

	Matrix4x4 operator*(Vector3D v);
	std::array<VCoord, COLS>& operator[](std::size_t index) {return data[index];}
	const std::array<VCoord, COLS>& operator[](std::size_t index) const {return data[index];}

};

}
