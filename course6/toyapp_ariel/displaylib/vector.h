#pragma once

#include <array>
#include <algorithm>
#include <numeric>
#include <cmath>

template<typename T, std::size_t size>
class Vector
{
public:
    Vector(const std::array<T, size>& v) :  values(v) {}

    T Length() const
    {
        return std::sqrt(Dot(*this));
    }

    T Dot(const Vector& v) const
    {
        auto temp = TransformVectors<std::multiplies<T>>(v);
        return std::accumulate(temp.begin(), temp.end(), 0, std::plus<T>());
    }

    Vector operator / (T v) const
    {
       return Transform(std::bind2nd(std::divides<T>(), v));
    }

    Vector operator * (T v) const
    {
       return Transform(std::bind2nd(std::multiplies<T>(), v));
    }

    Vector operator - (Vector v) const
    {
        return TransformVectors<std::minus<T>>(v);
    }

    Vector operator + (const Vector& v) const
    {
        return TransformVectors<std::plus<T>>(v);
    }

private:
    std::array<T, size> values;

    template<typename F>
    Vector TransformVectors(const Vector& v) const
    {
        std::array<T, size> temp;
        std::transform(values.begin(),values.end(), v.values.begin(), temp.begin(), F());
        return Vector(temp);
    }

    template<typename F>
    Vector Transform(F f) const
    {
        std::array<T, size> temp;
        std::transform(values.begin(),values.end(), temp.begin(), f);
        return Vector(temp);
    }
};
