#pragma once

#include <array>

namespace Display {

template <class TValue, size_t TDimentions, class TDecoratedType = TValue>
class VectorCommon
{
private:
	using TSelf = VectorCommon<TValue, TDimentions>;

protected:
	std::array<TValue, TDimentions> _data;

public:
	TDecoratedType operator + (const TDecoratedType& right)
	{
		auto return_value = TDecoratedType(*this);
		for (auto i = 0; i < TDimentions; i++)
			return_value._data[i] += right._data[i];
		return return_value;
	}

	TDecoratedType operator * (double scale)
	{
		auto return_value = TDecoratedType(*this);
		for (auto i = 0; i < TDimentions; i++)
			return_value._data[i] *= scale;
		return return_value;
	}

	TValue& operator[] (int i) { return _data[i]; }

	const TValue& operator[] (int i) const { return _data[i]; }
};

// 2 dimentional template vector decorator. Decorator needed only to provide x(), y() interface.
template <class TValue>
class Vector2DimDecorator : public VectorCommon<TValue, 2, Vector2DimDecorator<TValue>>
{
private:
	using TBase = VectorCommon<TValue, 2, Vector2DimDecorator<TValue>>;

public:
	Vector2DimDecorator() {}

	Vector2DimDecorator(TValue xx, TValue yy) :
		Vector2DimDecorator()
	{
		(*this)[0] = xx;
		(*this)[1] = yy;
	}

	Vector2DimDecorator(const TBase& original) :
		Vector2DimDecorator(original[0], original[1])
	{}

	TValue& x() { return _data[0]; }
	TValue& y() { return _data[1]; }

	const TValue& x() const { return _data[0]; }
	const TValue& y() const { return _data[1]; }
};


// 3 dimentional template vector. Decorator needed only to provide x(), y(), z() interface.
template <class TValue>
class Vector3DimDecorator : public VectorCommon<TValue, 3, Vector3DimDecorator<TValue>>
{
private:
	using TBase = VectorCommon<TValue, 3, Vector3DimDecorator<TValue>>;

public:
	TValue& x() { return _data[0]; }
	TValue& y() { return _data[1]; }
	TValue& z() { return _data[2]; }

	const TValue& x() const { return _data[0]; }
	const TValue& y() const { return _data[1]; }
	const TValue& z() const { return _data[2]; }

	Vector3DimDecorator() {}

	Vector3DimDecorator(TValue xx, TValue yy, TValue zz) :
		Vector3DimDecorator()
	{
		(*this)[0] = xx;
		(*this)[1] = yy;
		(*this)[2] = zz;
	}

	Vector3DimDecorator(const TBase& original) :
		Vector3DimDecorator(original[0], original[1], original[2])
	{}
};

using Vector2D = Vector2DimDecorator<double>;

using Vector3D = Vector3DimDecorator<double>;

}