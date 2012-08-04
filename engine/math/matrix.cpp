// File:        math/matrix.cpp
// Author:      Mitchell Harvey
// Date:        4/8/2012
//

#include <cmath>
#include "math/matrix.h"
#include "math/vector.h"

namespace engine {
namespace math {

const matrix3x3 matrix3x3::IDENTITY;
const matrix4x4 matrix4x4::IDENTITY;

matrix4x4 RotationMatrixX(float radians)
{
    float c = cos(radians);
    float s = sin(radians);

    matrix4x4 rot;

    rot.m22 = c;
    rot.m32 = -s;
    rot.m23 = s;
    rot.m33 = c;
   
    return rot;
}
//------------------------------------------------------------------------------------------------------------------------
matrix4x4 RotationMatrixY(float radians)
{
    float c = cos(radians);
    float s = sin(radians);
    
    matrix4x4 rot;

    rot.m11 = c;
    rot.m31 = s;
    rot.m13 = -s;
    rot.m33 = c;

    return rot;
}
//------------------------------------------------------------------------------------------------------------------------
matrix4x4 RotationMatrixZ(float radians)
{
    float c = cos(radians);
    float s = sin(radians);

    matrix4x4 rot;

    rot.m11 = c;
    rot.m21 = -s;
    rot.m12 = s;
    rot.m22 = c;

    return rot;
}
//------------------------------------------------------------------------------------------------------------------------
matrix4x4 RotationMatrix(float radians, const vector3 &axis)
{
    float c = cos(radians);
    float s = sin(radians);

    matrix4x4 rot;

    rot.m11 = c + ((axis.x * axis.x) * (1.0f - c));
    rot.m21 = (axis.y * axis.x * (1.0f  - c)) + (axis.z * s);
    rot.m31 = (axis.z * axis.x * (1.0f - c)) - (axis.y * s);

    rot.m12 = (axis.x * axis.y * (1.0f - c)) - (axis.z * s);
    rot.m22 = c + (axis.y * axis.y * (1.0f - c));
    rot.m32 = (axis.z * axis.y * (1.0f - c)) + (axis.x * s);

    rot.m13 = (axis.x * axis.z * (1.0f - c)) + (axis.y * s);
    rot.m23 = (axis.y * axis.z * (1.0f - c)) - (axis.x * s);
    rot.m33 = c + (axis.z * axis.z * (1.0f - c));

    return rot;
}
//------------------------------------------------------------------------------------------------------------------------
matrix4x4 InverseMatrix(const matrix4x4 &m)
{
    // http://www.cg.info.hiroshima-cu.ac.jp/~miyazaki/knowledge/teche23.html

    // TODO: Write the determinant function so we can early out if neccesary

    matrix4x4 inverse;
    inverse.m11 = m.m22*m.m33*m.m44 + m.m32*m.m43*m.m24 + m.m42*m.m23*m.m34 - m.m22*m.m43*m.m34 - m.m32*m.m23*m.m44 - m.m42*m.m33*m.m24;
    inverse.m21 = m.m21*m.m43*m.m34 + m.m31*m.m23*m.m44 + m.m41*m.m33*m.m24 - m.m21*m.m33*m.m44 - m.m31*m.m43*m.m24 - m.m41*m.m23*m.m34;
    inverse.m31 = m.m21*m.m32*m.m44 + m.m31*m.m42*m.m24 + m.m41*m.m22*m.m34 - m.m21*m.m42*m.m34 - m.m31*m.m22*m.m44 - m.m41*m.m32*m.m24;
    inverse.m41 = m.m21*m.m42*m.m33 + m.m31*m.m22*m.m43 + m.m41*m.m32*m.m23 - m.m21*m.m32*m.m43 - m.m31*m.m42*m.m23 - m.m41*m.m22*m.m33;
    inverse.m12 = m.m12*m.m43*m.m34 + m.m32*m.m13*m.m44 + m.m42*m.m33*m.m14 - m.m12*m.m33*m.m44 - m.m32*m.m43*m.m14 - m.m42*m.m13*m.m34;
    inverse.m22 = m.m11*m.m33*m.m44 + m.m31*m.m43*m.m14 + m.m41*m.m13*m.m34 - m.m11*m.m43*m.m34 - m.m31*m.m13*m.m44 - m.m41*m.m33*m.m14;
    inverse.m32 = m.m11*m.m42*m.m34 + m.m31*m.m12*m.m44 + m.m41*m.m32*m.m14 - m.m11*m.m32*m.m44 - m.m31*m.m42*m.m14 - m.m41*m.m12*m.m34;
    inverse.m42 = m.m11*m.m32*m.m43 + m.m31*m.m42*m.m13 + m.m41*m.m12*m.m33 - m.m11*m.m42*m.m33 - m.m31*m.m12*m.m43 - m.m41*m.m32*m.m13;
    inverse.m13 = m.m12*m.m23*m.m44 + m.m22*m.m43*m.m14 + m.m42*m.m13*m.m24 - m.m12*m.m43*m.m24 - m.m22*m.m13*m.m44 - m.m42*m.m23*m.m14;
    inverse.m23 = m.m11*m.m43*m.m24 + m.m21*m.m13*m.m44 + m.m41*m.m23*m.m14 - m.m11*m.m23*m.m44 - m.m21*m.m43*m.m14 - m.m41*m.m13*m.m24;
    inverse.m33 = m.m11*m.m22*m.m44 + m.m21*m.m42*m.m14 + m.m41*m.m12*m.m24 - m.m11*m.m42*m.m24 - m.m21*m.m12*m.m44 - m.m41*m.m22*m.m14;
    inverse.m43 = m.m11*m.m42*m.m23 + m.m21*m.m12*m.m43 + m.m41*m.m22*m.m13 - m.m11*m.m22*m.m43 - m.m21*m.m42*m.m13 - m.m41*m.m12*m.m23;
    inverse.m14 = m.m12*m.m33*m.m24 + m.m22*m.m13*m.m34 + m.m32*m.m23*m.m14 - m.m12*m.m23*m.m34 - m.m22*m.m33*m.m14 - m.m32*m.m13*m.m24;
    inverse.m24 = m.m11*m.m23*m.m34 + m.m21*m.m33*m.m14 + m.m31*m.m13*m.m24 - m.m11*m.m33*m.m24 - m.m21*m.m13*m.m34 - m.m31*m.m23*m.m14;
    inverse.m34 = m.m11*m.m32*m.m24 + m.m21*m.m12*m.m34 + m.m31*m.m22*m.m14 - m.m11*m.m22*m.m34 - m.m21*m.m32*m.m14 - m.m31*m.m12*m.m24;
    inverse.m44 = m.m11*m.m22*m.m33 + m.m21*m.m32*m.m13 + m.m31*m.m12*m.m23 - m.m11*m.m32*m.m23 - m.m21*m.m12*m.m33 - m.m31*m.m22*m.m13;
    return inverse;
}
} // engine
} // math
