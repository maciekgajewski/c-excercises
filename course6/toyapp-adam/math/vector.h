#pragma once

#include <cassert>
#include <array>
#include <cmath>
#include <limits>
#include <type_traits>

namespace Math {

template<typename T>
using IsFloatingPoint = std::enable_if_t<std::is_floating_point<T>::value>;

template<typename Type, unsigned Dimensions>
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

	bool operator==(const Vector& other) const
	{
		for (unsigned i = 0; i < Dimensions; ++i)
			if (!ApproximatelyEquals(mComponents[i], other[i]))
				return false;
		return true;
	}

	bool operator!=(const Vector& other) const
	{
		return !this->operator==(other);
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

	template<typename FloatType = float, typename = IsFloatingPoint<FloatType>>
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

	template<typename FloatType = float, typename = IsFloatingPoint<FloatType>>
	Vector operator*(FloatType scalar) const
	{
		return Vector{*this} *= scalar;
	}

	Vector operator-(const Vector& rhs) const
	{
		return Vector{*this} -= rhs;
	}

	template<typename FloatType = float, typename = IsFloatingPoint<FloatType>>
	Vector Normalized() const
	{
		auto length = Length();
		return !ApproximatelyEquals(length, 0.0)
				? Vector{*this} *= 1.0 / length
				: Vector{Type{1.0}, Type{0.0}};
	}

	template<typename FloatType = float, typename = IsFloatingPoint<FloatType>>
	FloatType Dot(const Vector& rhs) const
	{
		FloatType result{0.0};
		for (unsigned i = 0; i < Dimensions; ++i)
			result += mComponents[i] * rhs[i];
		return result;
	}

	template<typename FloatType = float, typename = IsFloatingPoint<FloatType>>
	FloatType Length() const
	{
		return std::sqrt(Dot(*this));
	}

	friend std::ostream& operator<<(std::ostream& stream, const Vector& vector)
	{
		for (unsigned i = 0; i < Dimensions - 1; ++i)
			stream << vector[i] << ',';
		stream << vector[Dimensions - 1];
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
