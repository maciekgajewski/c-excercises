#pragma once

#include <cassert>

#include "float4.h"
#include "float3.h"
#include <SDL2/SDL_main.h>

class Mat4
{
public:
    //The four columns of the matrix
    Float4 c0;
    Float4 c1;
    Float4 c2;
    Float4 c3;

    Mat4(float m00, float m01, float m02, float m03,
         float m10, float m11, float m12, float m13,
         float m20, float m21, float m22, float m23,
         float m30, float m31, float m32, float m33)
    {
            c0 = {m00, m10, m20, m30};
            c1 = {m01, m11, m21, m31};
            c2 = {m02, m12, m22, m32};
            c3 = {m03, m13, m23, m33};
    }

    Mat4(Float4 c0, Float4 c1, Float4 c2, Float4 c3) : c0(c0), c1(c1), c2(c2), c3(c3)
    {

    }

    float& operator () (int row, int column)
    {
        assert(row >= 0 && row <= 3);
        assert(column >= 0 && column <= 3);

        return  *(&(&c0 + column)->x + row);
    }

    Float4 operator * (const Float4& v) const
    {
        return
        {
            c0.x * v.x + c1.x * v.y + c2.x * v.z + c3.x * v.w,
            c0.y * v.x + c1.y * v.y + c2.y * v.z + c3.y * v.w,
            c0.z * v.x + c1.z * v.y + c2.z * v.z + c3.z * v.w,
            c0.w * v.x + c1.w * v.y + c2.w * v.z + c3.w * v.w
        };
    }

    static Mat4 CreateIdentity()
    {
        return
        {
            { 1.0f, 0.0f, 0.0f, 0.0f },
            { 0.0f, 1.0f, 0.0f, 0.0f },
            { 0.0f, 0.0f, 1.0f, 0.0f },
            { 0.0f, 0.0f, 0.0f, 1.0f }
          };
    }

    static Mat4 CreateTranslationMatrix(const Float3& v)
    {
        Mat4 result = CreateIdentity();
        result(0, 3) = v.x;
        result(1, 3) = v.y;
        result(2, 3) = v.z;

        return result;
    }

    static Mat4 CreateScaleMatrix(float v)
    {
        Mat4 result = CreateIdentity();
        result(0, 0) = v;
        result(1, 1) = v;
        result(2, 2) = v;

        return result;
    }
};

