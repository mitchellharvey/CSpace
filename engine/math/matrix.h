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
        // Row 1
        prod.m11 = (this->m11 * m.m11) + (this->m12 * m.m21) + (this->m13 * m.m31);
        prod.m12 = (this->m11 * m.m12) + (this->m12 * m.m22) + (this->m13 * m.m32);
        prod.m13 = (this->m11 * m.m13) + (this->m12 * m.m23) + (this->m13 * m.m33);
        // Row 2
        prod.m21 = (this->m21 * m.m11) + (this->m22 * m.m21) + (this->m23 * m.m31);
        prod.m22 = (this->m21 * m.m12) + (this->m22 * m.m22) + (this->m23 * m.m32);
        prod.m23 = (this->m21 * m.m13) + (this->m22 * m.m23) + (this->m23 * m.m33);
        // Row 3
        prod.m31 = (this->m31 * m.m11) + (this->m32 * m.m21) + (this->m33 * m.m31);
        prod.m32 = (this->m31 * m.m12) + (this->m32 * m.m22) + (this->m33 * m.m32);
        prod.m33 = (this->m31 * m.m13) + (this->m32 * m.m23) + (this->m33 * m.m33);

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
    float m11, m21, m31, _41; // x
    float m12, m22, m32, _42; // y
    float m13, m23, m33, _43; // z
    float _14, _24, _34, _44; // w

    //float m11, m12, m13, _14;
    //float m21, m22, m23, _24;
    //float m31, m32, m33, _34;
    //float _41, _42, _43, _44;

    static const matrix4x4 IDENTITY;

    inline matrix4x4(const float * const f) { set(f); }
    inline matrix4x4(const matrix3x3 &v) { memcpy(this, &v, sizeof(matrix4x4)); }
    inline matrix4x4(void) { memset(this, 0, sizeof(matrix4x4)); m11 = m22 = m33 = _44 = 1.0f; }
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
        sum.m11 += m.m11; sum.m12 += m.m12; sum.m13 += m.m13;  sum._14 += m._14;
        sum.m21 += m.m21; sum.m22 += m.m22; sum.m23 += m.m23;  sum._24 += m._24;
        sum.m31 += m.m31; sum.m32 += m.m32; sum.m33 += m.m33;  sum._34 += m._34;
        sum._41 += m._41; sum._42 += m._42; sum._43 += m._43;  sum._44 += m._44;
        return sum;
    }
    inline matrix4x4 &operator+=(const matrix4x4 &m)
    {
        this->m11 += m.m11; this->m12 += m.m12; this->m13 += m.m13;  this->_14 += m._14;
        this->m21 += m.m21; this->m22 += m.m22; this->m23 += m.m23;  this->_24 += m._24;
        this->m31 += m.m31; this->m32 += m.m32; this->m33 += m.m33;  this->_34 += m._34;
        this->_41 += m._41; this->_42 += m._42; this->_43 += m._43;  this->_44 += m._44;
        return *this;
    }
    inline const matrix4x4 operator-(const matrix4x4 &m) const
    {
        matrix4x4 sub(*this);
        sub.m11 -= m.m11; sub.m12 -= m.m12; sub.m13 -= m.m13;  sub._14 -= m._14;
        sub.m21 -= m.m21; sub.m22 -= m.m22; sub.m23 -= m.m23;  sub._24 -= m._24;
        sub.m31 -= m.m31; sub.m32 -= m.m32; sub.m33 -= m.m33;  sub._34 -= m._34;
        sub._41 -= m._41; sub._42 -= m._42; sub._43 -= m._43;  sub._44 -= m._44;
        return sub;
    }
    inline matrix4x4 &operator-=(const matrix4x4 &m)
    {
        this->m11 -= m.m11; this->m12 -= m.m12; this->m13 -= m.m13;  this->_14 -= m._14;
        this->m21 -= m.m21; this->m22 -= m.m22; this->m23 -= m.m23;  this->_24 -= m._24;
        this->m31 -= m.m31; this->m32 -= m.m32; this->m33 -= m.m33;  this->_34 -= m._34;
        this->_41 -= m._41; this->_42 -= m._42; this->_43 -= m._43;  this->_44 -= m._44;
        return *this;
    }
    inline matrix4x4 operator*(const matrix4x4 &m) const
    {
        matrix4x4 prod;
        // Row 1
        prod.m11 = (this->m11 * m.m11) + (this->m12 * m.m21) + (this->m13 * m.m31) + (this->_14 * m._41);
        prod.m12 = (this->m11 * m.m12) + (this->m12 * m.m22) + (this->m13 * m.m32) + (this->_14 * m._42);
        prod.m13 = (this->m11 * m.m13) + (this->m12 * m.m23) + (this->m13 * m.m33) + (this->_14 * m._43);
        prod._14 = (this->m11 * m._14) + (this->m12 * m._24) + (this->m13 * m._34) + (this->_14 * m._44);
        // Row 2
        prod.m21 = (this->m21 * m.m11) + (this->m22 * m.m21) + (this->m23 * m.m31) + (this->_24 * m._41);
        prod.m22 = (this->m21 * m.m12) + (this->m22 * m.m22) + (this->m23 * m.m32) + (this->_24 * m._41);
        prod.m23 = (this->m21 * m.m13) + (this->m22 * m.m23) + (this->m23 * m.m33) + (this->_24 * m._41);
        prod._24 = (this->m21 * m._14) + (this->m22 * m._24) + (this->m23 * m._34) + (this->_24 * m._41);
        // Row 3
        prod.m31 = (this->m31 * m.m11) + (this->m32 * m.m21) + (this->m33 * m.m31) + (this->_34 * m._41);
        prod.m32 = (this->m31 * m.m12) + (this->m32 * m.m22) + (this->m33 * m.m32) + (this->_34 * m._42);
        prod.m33 = (this->m31 * m.m13) + (this->m32 * m.m23) + (this->m33 * m.m33) + (this->_34 * m._43);
        prod._34 = (this->m31 * m._14) + (this->m32 * m._24) + (this->m33 * m._34) + (this->_34 * m._44);
        // Row 4
        prod._41 = (this->_41 * m.m11) + (this->_42 * m.m21) + (this->_43 * m.m31) + (this->_44 * m._41);
        prod._42 = (this->_41 * m.m12) + (this->_42 * m.m22) + (this->_43 * m.m32) + (this->_44 * m._42);
        prod._43 = (this->_41 * m.m13) + (this->_42 * m.m23) + (this->_43 * m.m33) + (this->_44 * m._43);
        prod._44 = (this->_41 * m._14) + (this->_42 * m._24) + (this->_43 * m._34) + (this->_44 * m._44);

        return prod;
    }
    inline matrix4x4 &operator*=(const matrix4x4 &m)
    {
        *this = *this * m;
        return *this;
    }
};


} // math
} // engine
#endif // ENGINE_MATH_VECTOR3_H_
