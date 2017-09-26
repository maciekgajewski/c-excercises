#pragma once

#include "vector3d.h"

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