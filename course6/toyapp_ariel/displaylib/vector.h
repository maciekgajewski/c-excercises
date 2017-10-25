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
    Vector(int n)
    {
        std::for_each(values.begin(), values.end(), [n](T& current){current = n;});
    }

    T operator[](int i) const
    {
        return values[i];
    }

    T& operator[](int i)
    {
        return values[i];
    }

    T Length() const
    {
        return std::sqrt(Dot(*this));
    }

    T Dot(const Vector& v) const
    {
        auto temp = TransformVectors(v, [](T a, T b) -> T {return a * b;});
        return std::accumulate(temp.begin(), temp.end(), 0, [](T a, T b) -> T {return a + b;});
    }

    Vector operator / (T v) const
    {
       return Transform([&v](T a) -> T {return a / v;});
    }

    Vector operator * (T v) const
    {
       return Transform([&v](T a) -> T {return a * v;});
    }

    Vector operator - (Vector v) const
    {
        return TransformVectors(v, [&v](T a, T b) -> T {return a - b;});
    }

    Vector operator + (const Vector& v) const
    {
        return TransformVectors(v, [&v](T a, T b) -> T {return a + b;});
    }

    const T* begin(){return values.cbegin();}

    const T* end(){return values.cend();}

private:
    std::array<T, size> values;

    template<typename F>
    Vector TransformVectors(const Vector& v, F f) const
    {
        std::array<T, size> temp;
        std::transform(values.begin(),values.end(), v.values.begin(), temp.begin(), f);
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
