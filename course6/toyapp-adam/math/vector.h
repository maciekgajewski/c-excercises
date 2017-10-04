#pragma once

#include <cassert>
#include <array>
#include <cmath>
#include <limits>

namespace Math {

template<typename Type, unsigned Dimensions, typename FloatType = float>
class Vector
{
public:
	using Component = Type;

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

	friend bool operator==(const Vector& lhs, const Vector& rhs)
	{
		for (unsigned i = 0; i < Dimensions; ++i)
			if (!ApproximatelyEquals(lhs[i], rhs[i]))
				return false;
		return true;
	}

	friend bool operator!=(const Vector& lhs, const Vector& rhs)
	{
		return !operator==(lhs, rhs);
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

	Vector& operator*=(FloatType scalar)
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

	Vector operator*(FloatType scalar) const
	{
		return Vector{*this} *= scalar;
	}

	Vector operator-(const Vector& rhs) const
	{
		return Vector{*this} -= rhs;
	}

	Vector Normalized() const
	{
		auto length = Length();
		return !ApproximatelyEquals(length, 0.0)
				? Vector{*this} *= 1.0 / length
				: Vector{Type{1.0}, Type{0.0}};
	}

	FloatType Dot(const Vector& rhs) const
	{
		FloatType result{0.0};
		for (unsigned i = 0; i < Dimensions; ++i)
			result += mComponents[i] * rhs[i];
		return result;
	}

	FloatType Length() const
	{
		return std::sqrt(Dot(*this));
	}

	friend std::ostream& operator<<(std::ostream& stream, const Vector& vector)
	{
		stream << vector[0] << ',' << vector[1];
		return stream;
	}

private:
	std::array<Type, Dimensions> mComponents;

	static bool ApproximatelyEquals(Type a, Type b)
	{
		using std::abs;
		return abs(a - b) <= (abs(a) < abs(b) ? abs(b) : abs(a)) * std::numeric_limits<Type>::epsilon();
	};
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
