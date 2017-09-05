#include "float3.h"

Float3::Float3(const float& x, const float& y, const float& z) : x(x), y(y), z(z)
{

}

Float3::Float3(float f) : x(f), y(f), z(f)
{

}

Float3::Float3() : x(0), y(0), z(0)
{

}

Float3 Float3::Clamp() const
{
    return Float3(Float3::Clamp(x), Float3::Clamp(y), Float3::Clamp(z));
}

float Float3::Length() const
{
    return (float)std::sqrt(this->Dot(*this));
}

float Float3::Dot(const Float3 &f) const
{
    return x * f.x + y * f.y + z * f.z;
}

Float3 Float3::operator / (const float& f) const
{
    return Float3(x / f, y / f, z / f);
}

Float3 Float3::operator -(const Float3& f) const
{
    return Float3(x - f.x, y - f.y, z - f.z);
}

Float3 Float3::operator +(const Float3& f) const
{
    return Float3(x + f.x, y + f.y, z + f.z);
}

Float3 Float3::operator *(const float& f) const
{
    return Float3(x * f, y * f, z * f);
}

Float3 Float3::operator *(const Float3& f) const
{
    return Float3(x * f.x, y * f.y, z * f.z);
}

Float3 Float3::Normalize() const
{
    return (*this) / (this->Length());
}
