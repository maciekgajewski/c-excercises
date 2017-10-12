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

// 2 dimentional template vector decorator. Decorator needed only to provide x, y
template <class TValue>
class Vector2DimDecorator : public VectorCommon<TValue, 2, Vector2DimDecorator<TValue>>
{
private:
	using TBase = VectorCommon<TValue, 2, Vector2DimDecorator<TValue>>;

public:
	TValue &x, &y;

	Vector2DimDecorator() :
		x(_data[0]),
		y(_data[1])
	{}

	Vector2DimDecorator(TValue xx, TValue yy) :
		Vector2DimDecorator()
	{
		(*this)[0] = xx;
		(*this)[1] = yy;
	}

	Vector2DimDecorator(TBase undecorated) :
		Vector2DimDecorator(undecorated[0], undecorated[1])
	{}

	Vector2DimDecorator(const Vector2DimDecorator& original) :
		Vector2DimDecorator(original[0], original[1])
	{}
};


// 3 dimentional templte vector. Decorator needed only to provide x, y, z
template <class TValue>
class Vector3DimDecorator : public VectorCommon<TValue, 3, Vector3DimDecorator<TValue>>
{
private:
	using TBase = VectorCommon<TValue, 3, Vector3DimDecorator<TValue>>;
public:
	TValue &x, &y, &z;

	Vector3DimDecorator() :
		x(_data[0]),
		y(_data[1]),
		z(_data[2])
	{}

	Vector3DimDecorator(TValue xx, TValue yy, TValue zz) :
		Vector3DimDecorator()
	{
		(*this)[0] = xx;
		(*this)[1] = yy;
		(*this)[2] = zz;
	}

	Vector3DimDecorator(TBase undecorated) :
		Vector3DimDecorator(undecorated[0], undecorated[1], undecorated[2])
	{}

	Vector3DimDecorator(const Vector3DimDecorator& original) :
		Vector3DimDecorator(original[0], original[1], original[2])
	{}
};

using Vector2D = Vector2DimDecorator<double>;

using Vector3D = Vector3DimDecorator<double>;

}