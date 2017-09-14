#pragma once

#include <cmath>

class Float3
{
public:
    float x, y ,z;
    Float3(float x, float y, float z) : x(x), y(y), z(z)
    {

    }

    Float3(float f) : x(f), y(f), z(f)
    {

    }

    Float3() : x(0), y(0), z(0)
    {

    }

    Float3 Clamp01() const
    {
        return Float3(Clamp01(x), Clamp01(y), Clamp01(z));
    }

    float Length() const
    {
        return (float)std::sqrt(this->Dot(*this));
    }

    float Dot(Float3 f) const
    {
        return x * f.x + y * f.y + z * f.z;
    }

    Float3 Cross (Float3 f)
    {
        return Float3(y * f.z - z * f.y, z * f.x - x * f.z, x * f.y - y * f.x);
    }

    Float3 operator / (float f) const
    {
        return Float3(x / f, y / f, z / f);
    }

    Float3 operator -(Float3 f) const
    {
        return Float3(x - f.x, y - f.y, z - f.z);
    }

    Float3 operator +(Float3 f) const
    {
        return Float3(x + f.x, y + f.y, z + f.z);
    }

    Float3 operator *(float f) const
    {
        return Float3(x * f, y * f, z * f);
    }

    Float3 operator *(Float3 f) const
    {
        return Float3(x * f.x, y * f.y, z * f.z);
    }

    Float3 Normalize() const
    {
        return (*this) / (this->Length());
    }

    static float Clamp01(const float& x)
    {
        return x < 0 ? 0 : x > 1 ? 1 : x;
    }

    static Float3 Lerp(Float3 v0, Float3 v1, float t)
    {
      return v0  * (1 - t) + v1 * t;
    }

    static float Lerp(float v0, float v1, float t)
    {
      return v0  * (1 - t) + v1 * t;
    }
};

