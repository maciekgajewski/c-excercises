#include "matrix.h"

namespace Draw{

void Matrix4x4::Set(size_t row, size_t col, VCoord value)
{
	data.at(row).at(col) = value;
}

VCoord Matrix4x4::Get(size_t row, size_t col)
{
	return data.at(row).at(col);
}

}
