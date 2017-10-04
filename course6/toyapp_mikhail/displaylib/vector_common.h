#pragma once

namespace Display{

template <class TValue, int TDimentions>
class VectorCommon
{
	// No constructor for vector without specification
	VectorCommon() = delete;
};

// Specification for 2 dimentional vector
template <class TValue>
class VectorCommon<TValue, 2>
{
private:
	using TSelf = VectorCommon<TValue, 2>;
public:
	TValue x, y;

	TSelf operator + (const TSelf& v)
	{
		auto r = TSelf(*this);
		r.x += v.x;
		r.y += v.y;
		return r;
	}

	TSelf operator * (double scale)
	{
		auto r = TSelf(*this);
		r.x *= scale;
		r.y *= scale;
		return r;
	}
};

// Specification for 3d vector
template <class TValue>
class VectorCommon<TValue, 3>
{
private:
	using TSelf = VectorCommon<TValue, 3>;
public:
	TValue x, y, z;

	TSelf operator + (const TSelf& v)
	{
		auto r = TSelf(*this);
		r.x += v.x;
		r.y += v.y;
		r.z += v.z;
		return r;
	}
};

}