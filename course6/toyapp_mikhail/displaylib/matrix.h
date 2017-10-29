#pragma once

#include "vector_common.h"

namespace Display {

class Matrix
{
public:
	Vector3D operator * (Vector3D v)
	{
		return v;
	}
};

}