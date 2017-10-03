#pragma once

#include <cassert>
#include <array>
#include <cmath>

namespace Math {

template<typename Type, unsigned Dimensions>
class Vector
{
public:
	Vector()
	:	mComponents{{0}}
	{}

	template<typename... Args>
	Vector(Args... args)
	:	mComponents{{args...}}
	{}

	Vector(const Vector<Type, Dimensions-1>& other, Type lastComponent)
	{
		for (unsigned i = 0; i < Dimensions-1; ++i)
			mComponents[i] = other[i];
		mComponents[Dimensions-1] = lastComponent;
	}

	Vector(const Vector& other)
	{
		operator=(other);
	}

	operator Vector<Type, Dimensions-1>() const
	{
		Vector<Type, Dimensions-1> result;
		for (unsigned i = 0; i < Dimensions-1; ++i)
			result[i] = mComponents[i];
		return result;
	}

	Vector& operator=(const Vector& other)
	{
		for (unsigned i = 0; i < Dimensions; ++i)
			mComponents[i] = other[i];
		return *this;
	}

	Vector& operator+=(const Vector& other)
	{
		for (unsigned i = 0; i < Dimensions; ++i)
			mComponents[i] += other[i];
		return *this;
	}

	Vector& operator*=(float scalar)
	{
		for (unsigned i = 0; i < Dimensions; ++i)
			mComponents[i] *= scalar;
		return *this;
	}

	Vector& operator-=(const Vector& other)
	{
		return operator+=(-other);
	}

	Type& operator[](unsigned index)
	{
		assert(index < Dimensions);
		return mComponents[index];
	}

	Type operator[](unsigned index) const
	{
		assert(index < Dimensions);
		return mComponents[index];
	}

	Vector operator-() const
	{
		Vector result;
		for (unsigned i = 0; i < Dimensions; ++i)
			result[i] = -mComponents[i];
		return result;
	}

	Vector operator+(const Vector& rhs) const
	{
		return Vector{*this} += rhs;
	}

	Vector operator*(float scalar) const
	{
		return Vector{*this} *= scalar;
	}

	Vector operator-(const Vector& rhs) const
	{
		return Vector{*this} -= rhs;
	}

	Vector Normalized() const
	{
		return Vector{*this} *= 1.0f / Length();
	}

	float Dot(const Vector& rhs) const
	{
		float result = 0.0f;
		for (unsigned i = 0; i < Dimensions; ++i)
			result += mComponents[i] * rhs[i];
		return result;
	}

	float Length() const
	{
		return std::sqrt(Dot(*this));
	}

private:
	std::array<Type, Dimensions> mComponents;
};


template<typename Type>
inline Vector<Type, 3> Cross(const Vector<Type, 3>& lhs, const Vector<Type, 3>& rhs)
{
	return {
		lhs[1] * rhs[2] - lhs[2] * rhs[1],
		lhs[2] * rhs[0] - lhs[0] * rhs[2],
		lhs[0] * rhs[1] - lhs[1] * rhs[0]
	};
}


using Vector2D = Vector<float, 2>;
using Vector3D = Vector<float, 3>;
using Vector4D = Vector<float, 4>;

}
