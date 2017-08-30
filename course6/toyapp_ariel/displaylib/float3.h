#ifndef FLOAT3_H
#define FLOAT3_H

#include <algorithm>
#include <math.h>

class Float3
{
public:
    float x, y ,z;
    Float3();
    Float3(float f);
    Float3(const float& x, const float& y, const float& z);
    Float3 Normalize() const;
    float Dot(const Float3& f) const;
    float Length() const;
    Float3 Clamp() const;
    Float3 operator / (const float& f) const;
    Float3 operator - (const Float3& f) const;
    Float3 operator + (const Float3& f) const;
    Float3 operator * (const float& f) const;
    Float3 operator * (const Float3& f) const;
    static float Clamp(const float& x)
    {
        return x < 0 ? 0 : x > 1 ? 1 : x;
    }
};

#endif // FLOAT3_H
