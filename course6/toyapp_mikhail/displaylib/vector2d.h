#pragma once

namespace Display {

	class Vector2D
	{
	public:
		double x, y;

		Vector2D operator + (const Vector2D& v)
		{
			auto r = Vector2D(*this);
			r.x += v.x;
			r.y += v.y;
			return r;
		}

		Vector2D operator * (double scale)
		{
			auto r = Vector2D(*this);
			r.x *= scale;
			r.y *= scale;
			return r;
		}
	};
}