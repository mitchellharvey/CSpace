// File:        renderer/Transform.cpp
// Author:      Mitchell Harvey
// Date:        6/29/2011
// 

#include "renderer/Transform.h"
#include "math/util.h"

namespace engine {
namespace renderer {

//------------------------------------------------------------------------------------------------------------------------
Transform::Transform(void)
{
}
//------------------------------------------------------------------------------------------------------------------------
Transform::Transform(const Transform &c)
{
    _transform.set((const float * const)&(c._transform));
}
//------------------------------------------------------------------------------------------------------------------------
Transform::Transform(const matrix4x4 &m)
{
    _transform.set((const float * const)&m);
}
//------------------------------------------------------------------------------------------------------------------------
Transform::Transform(const matrix3x3 &m)
{
    memcpy(&_transform.m11, &m.m11, sizeof(vector3));
    memcpy(&_transform.m21, &m.m21, sizeof(vector3));
    memcpy(&_transform.m31, &m.m31, sizeof(vector3));
}
//------------------------------------------------------------------------------------------------------------------------
Transform::~Transform(void)
{
}
//------------------------------------------------------------------------------------------------------------------------
matrix4x4 &Transform::GetTransformMatrix(void)
{
    return _transform;
}
//------------------------------------------------------------------------------------------------------------------------
vector3 Transform::GetTranslation(void) const
{
    return vector3(_transform._14, _transform._24, _transform._34);
}
//------------------------------------------------------------------------------------------------------------------------
vector3 Transform::GetXAxis(void) const
{
    return vector3(_transform.m11, _transform.m21, _transform.m31);
}
//------------------------------------------------------------------------------------------------------------------------
vector3 Transform::GetYAxis(void) const
{
    return vector3(_transform.m12, _transform.m22, _transform.m32);
}
//------------------------------------------------------------------------------------------------------------------------
vector3 Transform::GetZAxis(void) const
{
    return vector3(_transform.m13, _transform.m23, _transform.m33);
}
//------------------------------------------------------------------------------------------------------------------------
void Transform::SetTranslation(const vector3 &t)
{
    _transform._14 = t.x;
    _transform._24 = t.y;
    _transform._34 = t.z;
}
//------------------------------------------------------------------------------------------------------------------------
void Transform::SetTranslation(float x, float y, float z)
{
    _transform._14 = x;
    _transform._24 = y;
    _transform._34 = z;
}
//------------------------------------------------------------------------------------------------------------------------
void Transform::SetXAxis(float x, float y, float z)
{
    _transform.m11 = x;
    _transform.m21 = y;
    _transform.m31 = z;
}
//------------------------------------------------------------------------------------------------------------------------
void Transform::SetXAxis(const vector3 &v)
{
    _transform.m11 = v.x;
    _transform.m21 = v.y;
    _transform.m31 = v.z;
}
//------------------------------------------------------------------------------------------------------------------------
void Transform::SetYAxis(float x, float y, float z)
{
    _transform.m12 = x;
    _transform.m22 = y;
    _transform.m32 = z;
}
//------------------------------------------------------------------------------------------------------------------------
void Transform::SetYAxis(const vector3 &v)
{
    _transform.m12 = v.x;
    _transform.m22 = v.y;
    _transform.m32 = v.z;
}
//------------------------------------------------------------------------------------------------------------------------
void Transform::SetZAxis(float x, float y, float z)
{
    _transform.m13 = x;
    _transform.m23 = y;
    _transform.m33 = z;
}
//------------------------------------------------------------------------------------------------------------------------
void Transform::SetZAxis(const vector3 &v)
{
    _transform.m13 = v.x;
    _transform.m23 = v.y;
    _transform.m33 = v.z;
}
//------------------------------------------------------------------------------------------------------------------------
void Transform::ScaleXAxis(float s)
{
    _transform.m11 *= s;
    _transform.m21 *= s;
    _transform.m31 *= s;
}
//------------------------------------------------------------------------------------------------------------------------
void Transform::ScaleYAxis(float s)
{
    _transform.m12 *= s;
    _transform.m22 *= s;
    _transform.m32 *= s;
}
//------------------------------------------------------------------------------------------------------------------------
void Transform::ScaleZAxis(float s)
{
    _transform.m13 *= s;
    _transform.m23 *= s;
    _transform.m33 *= s;
}
//------------------------------------------------------------------------------------------------------------------------
void Transform::LookAt(const vector3 &p)
{
    static vector3 worldUp(0.0f, 1.0f, 0.0f);

    vector3 newForward, newUp, newRight;

    newForward = p - GetTranslation();
    v3Normalize(newForward);

    newRight = v3CrossProduct(newForward, worldUp);
    v3Normalize(newRight);
    
    newUp = v3CrossProduct(newRight, newForward);
    v3Normalize(newUp);

    SetXAxis(newRight);
    SetYAxis(newUp);
    SetZAxis(newForward);
}
//------------------------------------------------------------------------------------------------------------------------
void Transform::LookAt(float x, float y, float z)
{
    LookAt(vector3(x, y, z));
}
} // renderer
} // engine
