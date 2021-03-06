// File:        math/matrix.h
// Author:      Mitchell Harvey
// Date:        6/28/2011
//
// NOTE:        Matrices are laid out in column-major order so to easily translate for opengl
// TODO:        Study up on SSE instructions and caching to convert this into a vectorized library of SIMD instructions
//

#ifndef ENGINE_MATH_MATRIX_H_
#define ENGINE_MATH_MATRIX_H_

#include <memory.h>
#include "system\types.h"

namespace engine {
namespace math {

using system::BYTE;

struct vector3;
    
struct matrix3x3
{
    float m11, m21, m31;
    float m12, m22, m32;
    float m13, m23, m33;

    static const matrix3x3 IDENTITY;

    inline matrix3x3(const float * const f) { set(f); }
    inline matrix3x3(const matrix3x3 &v) { memcpy(this, &v, sizeof(matrix3x3)); }
    inline matrix3x3(void) { memset(this, 0, sizeof(matrix3x3)); m11 = m22 = m33 = 1.0f; }
    inline matrix3x3 &set(const float * const f)
    {
        memcpy(this, f, sizeof(matrix3x3));
        return *this;
    }   
    inline matrix3x3 &operator=(const matrix3x3 &m)
    {
        memcpy(this, &m, sizeof(matrix3x3));
        return *this;
    }
    inline bool operator==(const matrix3x3 &m) const
    {
        return memcmp(this, &m, sizeof(matrix3x3)) == 0;
    }
    inline bool operator!=(const matrix3x3 &m) const
    {
        return !(*this == m);
    }
    inline const matrix3x3 operator+(const matrix3x3 &m) const
    {
        matrix3x3 sum(*this);
        sum.m11 += m.m11; sum.m12 += m.m12; sum.m13 += m.m13;
        sum.m21 += m.m21; sum.m22 += m.m22; sum.m23 += m.m23;
        sum.m31 += m.m31; sum.m32 += m.m32; sum.m33 += m.m33;
        return sum;
    }
    inline matrix3x3 &operator+=(const matrix3x3 &m)
    {
        this->m11 += m.m11; this->m12 += m.m12; this->m13 += m.m13;
        this->m21 += m.m21; this->m22 += m.m22; this->m23 += m.m23;
        this->m31 += m.m31; this->m32 += m.m32; this->m33 += m.m33;
        return *this;
    }
    inline const matrix3x3 operator-(const matrix3x3 &m) const
    {
        matrix3x3 sub(*this);
        sub.m11 -= m.m11; sub.m12 -= m.m12; sub.m13 -= m.m13;
        sub.m21 -= m.m21; sub.m22 -= m.m22; sub.m23 -= m.m23;
        sub.m31 -= m.m31; sub.m32 -= m.m32; sub.m33 -= m.m33;
        return sub;
    }
    inline matrix3x3 &operator-=(const matrix3x3 &m)
    {
        this->m11 -= m.m11; this->m12 -= m.m12; this->m13 -= m.m13;
        this->m21 -= m.m21; this->m22 -= m.m22; this->m23 -= m.m23;
        this->m31 -= m.m31; this->m32 -= m.m32; this->m33 -= m.m33;
        return *this;
    }
    inline const matrix3x3 operator*(const matrix3x3 &m) const
    {
        matrix3x3 prod;

        prod.m11 = (this->m11 * m.m11) + (this->m21 * m.m12) + (this->m31 * m.m13);
        prod.m21 = (this->m11 * m.m21) + (this->m21 * m.m22) + (this->m31 * m.m23);
        prod.m31 = (this->m11 * m.m31) + (this->m21 * m.m32) + (this->m31 * m.m33);

        prod.m12 = (this->m12 * m.m11) + (this->m22 * m.m12) + (this->m32 * m.m13);
        prod.m22 = (this->m12 * m.m21) + (this->m22 * m.m22) + (this->m32 * m.m23);
        prod.m32 = (this->m12 * m.m31) + (this->m22 * m.m32) + (this->m32 * m.m33);

        prod.m13 = (this->m13 * m.m11) + (this->m23 * m.m12) + (this->m33 * m.m13);
        prod.m23 = (this->m13 * m.m21) + (this->m23 * m.m22) + (this->m33 * m.m23);
        prod.m33 = (this->m13 * m.m31) + (this->m23 * m.m32) + (this->m33 * m.m33);

        return prod;
    }
    inline matrix3x3 &operator*=(const matrix3x3 &m)
    {
        *this = *this * m;
        return *this;
    }
};

struct matrix4x4
{
    // Column Major
    float m11, m21, m31, m41; // x
    float m12, m22, m32, m42; // y
    float m13, m23, m33, m43; // z
    float m14, m24, m34, m44; // w

    static const matrix4x4 IDENTITY;

    inline matrix4x4(const float * const f) { set(f); }
    inline matrix4x4(const matrix3x3 &v) { memcpy(this, &v, sizeof(matrix4x4)); }
    inline matrix4x4(void) { memset(this, 0, sizeof(matrix4x4)); m11 = m22 = m33 = m44 = 1.0f; }
    inline matrix4x4 &set(const float * const f)
    {
        memcpy(this, f, sizeof(matrix4x4));
        return *this;
    }   
    inline matrix4x4 &operator=(const matrix4x4 &m)
    {
        memcpy(this, &m, sizeof(matrix4x4));
        return *this;
    }
    inline bool operator==(const matrix4x4 &m) const
    {
        return memcmp(this, &m, sizeof(matrix4x4)) == 0;
    }
    inline bool operator!=(const matrix4x4 &m) const
    {
        return !(*this == m);
    }
    inline const matrix4x4 operator+(const matrix4x4 &m) const
    {
        matrix4x4 sum(*this);
        sum.m11 += m.m11; sum.m12 += m.m12; sum.m13 += m.m13;  sum.m14 += m.m14;
        sum.m21 += m.m21; sum.m22 += m.m22; sum.m23 += m.m23;  sum.m24 += m.m24;
        sum.m31 += m.m31; sum.m32 += m.m32; sum.m33 += m.m33;  sum.m34 += m.m34;
        sum.m41 += m.m41; sum.m42 += m.m42; sum.m43 += m.m43;  sum.m44 += m.m44;
        return sum;
    }
    inline matrix4x4 &operator+=(const matrix4x4 &m)
    {
        this->m11 += m.m11; this->m12 += m.m12; this->m13 += m.m13;  this->m14 += m.m14;
        this->m21 += m.m21; this->m22 += m.m22; this->m23 += m.m23;  this->m24 += m.m24;
        this->m31 += m.m31; this->m32 += m.m32; this->m33 += m.m33;  this->m34 += m.m34;
        this->m41 += m.m41; this->m42 += m.m42; this->m43 += m.m43;  this->m44 += m.m44;
        return *this;
    }
    inline const matrix4x4 operator-(const matrix4x4 &m) const
    {
        matrix4x4 sub(*this);
        sub.m11 -= m.m11; sub.m12 -= m.m12; sub.m13 -= m.m13;  sub.m14 -= m.m14;
        sub.m21 -= m.m21; sub.m22 -= m.m22; sub.m23 -= m.m23;  sub.m24 -= m.m24;
        sub.m31 -= m.m31; sub.m32 -= m.m32; sub.m33 -= m.m33;  sub.m34 -= m.m34;
        sub.m41 -= m.m41; sub.m42 -= m.m42; sub.m43 -= m.m43;  sub.m44 -= m.m44;
        return sub;
    }
    inline matrix4x4 &operator-=(const matrix4x4 &m)
    {
        this->m11 -= m.m11; this->m12 -= m.m12; this->m13 -= m.m13;  this->m14 -= m.m14;
        this->m21 -= m.m21; this->m22 -= m.m22; this->m23 -= m.m23;  this->m24 -= m.m24;
        this->m31 -= m.m31; this->m32 -= m.m32; this->m33 -= m.m33;  this->m34 -= m.m34;
        this->m41 -= m.m41; this->m42 -= m.m42; this->m43 -= m.m43;  this->m44 -= m.m44;
        return *this;
    }
    inline matrix4x4 operator*(const matrix4x4 &m) const
    {
        matrix4x4 prod;

        prod.m11 = (this->m11 * m.m11) + (this->m21 * m.m12) + (this->m31 * m.m13) + (this->m41 * m.m14);
        prod.m21 = (this->m11 * m.m21) + (this->m21 * m.m22) + (this->m31 * m.m23) + (this->m41 * m.m24);
        prod.m31 = (this->m11 * m.m31) + (this->m21 * m.m32) + (this->m31 * m.m33) + (this->m41 * m.m34);
        prod.m41 = (this->m11 * m.m41) + (this->m21 * m.m42) + (this->m31 * m.m43) + (this->m41 * m.m44);

        prod.m12 = (this->m12 * m.m11) + (this->m22 * m.m12) + (this->m32 * m.m13) + (this->m42 * m.m14);
        prod.m22 = (this->m12 * m.m21) + (this->m22 * m.m22) + (this->m32 * m.m23) + (this->m42 * m.m24);
        prod.m32 = (this->m12 * m.m31) + (this->m22 * m.m32) + (this->m32 * m.m33) + (this->m42 * m.m34);
        prod.m42 = (this->m12 * m.m41) + (this->m22 * m.m42) + (this->m32 * m.m43) + (this->m42 * m.m44);

        prod.m13 = (this->m13 * m.m11) + (this->m23 * m.m12) + (this->m33 * m.m13) + (this->m43 * m.m14);
        prod.m23 = (this->m13 * m.m21) + (this->m23 * m.m22) + (this->m33 * m.m23) + (this->m43 * m.m24);
        prod.m33 = (this->m13 * m.m31) + (this->m23 * m.m32) + (this->m33 * m.m33) + (this->m43 * m.m34);
        prod.m43 = (this->m13 * m.m41) + (this->m23 * m.m42) + (this->m33 * m.m43) + (this->m43 * m.m44);

        prod.m14 = (this->m14 * m.m11) + (this->m24 * m.m12) + (this->m34 * m.m13) + (this->m44 * m.m14);
        prod.m24 = (this->m14 * m.m21) + (this->m24 * m.m22) + (this->m34 * m.m23) + (this->m44 * m.m24);
        prod.m34 = (this->m14 * m.m31) + (this->m24 * m.m32) + (this->m34 * m.m33) + (this->m44 * m.m34);
        prod.m44 = (this->m14 * m.m41) + (this->m24 * m.m42) + (this->m34 * m.m43) + (this->m44 * m.m44);

        return prod;
    }
    inline matrix4x4 &operator*=(const matrix4x4 &m)
    {
        *this = *this * m;
        return *this;
    }
};

matrix4x4 RotationMatrixX(float radians);
matrix4x4 RotationMatrixY(float radians);
matrix4x4 RotationMatrixZ(float radians);

matrix4x4 RotationMatrix(float radians, const vector3 &axis);

matrix4x4 InverseMatrix(const matrix4x4 &m);

} // math
} // engine
#endif // ENGINE_MATH_VECTOR3_H_
