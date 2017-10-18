#pragma once

#include <array>

namespace Display {

namespace Detail {
template <class TValue, size_t DIMENTIONS, class TConcreteVector>
class VectorBase
{
protected:
	std::array<TValue, DIMENTIONS> mData;

public:
	TConcreteVector operator + (const TConcreteVector& right)
	{
		auto return_value = TConcreteVector(*this);
		for (auto i = 0; i < DIMENTIONS; i++)
			return_value[i] += right[i];
		return return_value;
	}

	TConcreteVector operator * (double scale)
	{
		auto return_value = TConcreteVector(*this);
		for (auto i = 0; i < DIMENTIONS; i++)
			return_value[i] *= scale;
		return return_value;
	}

	TValue& operator[] (int i) { return mData[i]; }

	const TValue& operator[] (int i) const { return mData[i]; }
};
}

// 2 dimentional template vector. Implementetion needed only to provide x(), y() interface.
template <class TValue>
class Vector2 : public Detail::VectorBase<TValue, 2, Vector2<TValue>>
{
private:
	using TBase = Detail::VectorBase<TValue, 2, Vector2<TValue>>;

public:
	Vector2() = default;

	Vector2(TValue xx, TValue yy)
	{
		(*this)[0] = xx;
		(*this)[1] = yy;
	}

	Vector2(const TBase& original) :
		Vector2(original[0], original[1])
	{}

	TValue& x() { return mData[0]; }
	TValue& y() { return mData[1]; }

	const TValue& x() const { return mData[0]; }
	const TValue& y() const { return mData[1]; }
};


// 3 dimentional template vector. Implementetion needed to provide x(), y(), z() interface.
template <class TValue>
class Vector3 : public Detail::VectorBase<TValue, 3, Vector3<TValue>>
{
private:
	using TBase = Detail::VectorBase<TValue, 3, Vector3<TValue>>;

public:
	TValue& x() { return mData[0]; }
	TValue& y() { return mData[1]; }
	TValue& z() { return mData[2]; }

	const TValue& x() const { return mData[0]; }
	const TValue& y() const { return mData[1]; }
	const TValue& z() const { return mData[2]; }

	Vector3() = default;

	Vector3(TValue xx, TValue yy, TValue zz)
	{
		(*this)[0] = xx;
		(*this)[1] = yy;
		(*this)[2] = zz;
	}

	Vector3(const TBase& original) :
		Vector3(original[0], original[1], original[2])
	{}
};

// N dimentional template vector.
template <class TValue, size_t DIMENTIONS>
class VectorN : public Detail::VectorBase<TValue, DIMENTIONS, VectorN<TValue, DIMENTIONS>>
{
private:
	using TBase = Detail::VectorBase<TValue, DIMENTIONS, VectorN<TValue, DIMENTIONS>>;

public:
	VectorN() = default;

	VectorN(const TBase& original) :
		mData(original.mData)
	{}
};

using Vector2D = Vector2<double>;

using Vector3D = Vector3<double>;

}
