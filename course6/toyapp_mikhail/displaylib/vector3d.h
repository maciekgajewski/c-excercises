#pragma once

namespace Display {

	class Vector3D
	{
	public:
		double x, y, z;

		Vector3D operator + (const Vector3D& v)
		{
			auto r = Vector3D(*this);
			r.x += v.x;
			r.y += v.y;
			r.z += v.z;
			return r;
		}
	};

}