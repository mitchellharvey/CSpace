// File:        renderer/Camera.cpp
// Author:      Mitchell Harvey
// Date:        4/9/2012
// 

#include "math/util.h"
#include "renderer/Camera.h"

namespace engine {
namespace renderer {

Camera::Camera(void) :
 Transform()
,_fieldOfView(45.0f)
,_widthHeightRatio(0.0f)
,_nearPlane(1.0f)
,_farPlane(30.0f)
{
}
//------------------------------------------------------------------------------------------------------------------------
Camera::~Camera(void)
{
}
//------------------------------------------------------------------------------------------------------------------------
void Camera::SetFieldOfView(float fov)
{
    _fieldOfView = fov;
}
//------------------------------------------------------------------------------------------------------------------------
void Camera::SetWidthHeightRatio(float ratio)
{
    _widthHeightRatio = ratio;
}
//------------------------------------------------------------------------------------------------------------------------
void Camera::SetNearPlaneDistance(float near)
{
    _nearPlane = near;
}
//------------------------------------------------------------------------------------------------------------------------
void Camera::SetFarPlaneDistance(float far)
{
    _farPlane = far;
}
//------------------------------------------------------------------------------------------------------------------------
float Camera::GetFieldOfView(void) const
{
    return _fieldOfView;
}
//------------------------------------------------------------------------------------------------------------------------
float Camera::GetWidthHeightRatio(void) const
{
    return _widthHeightRatio;
}
//------------------------------------------------------------------------------------------------------------------------
float Camera::GetNearPlaneDistance(void) const
{
    return _nearPlane;
}
//------------------------------------------------------------------------------------------------------------------------
float Camera::GetFarPlaneDistance(void) const
{
    return _farPlane;
}
//------------------------------------------------------------------------------------------------------------------------
matrix4x4 Camera::GetProjectionMatrix(void) const
{
    // Thanks Lighthouse 3D
    // http://www.lighthouse3d.com/cg-topics/code-samples/opengl-3-3-glsl-1-5-sample/
    //

    matrix4x4 proj;
    float f = 1.0f / tan(_fieldOfView * (PI / 360.0f));

    proj.m11 = f / _widthHeightRatio;
    proj.m22 = f;
    proj.m33 = (_farPlane + _nearPlane) / (_nearPlane - _farPlane);
    proj.m34 = (2.0f * _farPlane * _nearPlane) / (_nearPlane - _farPlane);
    proj.m43 = -1.0f;
    proj.m44 = 0.0f;

    return proj;
}
//------------------------------------------------------------------------------------------------------------------------
matrix4x4 Camera::GetViewMatrix(void) const
{
    // Thanks Lighthouse 3D
    // http://www.lighthouse3d.com/cg-topics/code-samples/opengl-3-3-glsl-1-5-sample/
    //

    Transform view(*this);
    view.ScaleZAxis(-1.0f);
    view.SetTranslation(GetTranslation() * -1.0f);

    return view.GetTransformMatrix();
}
} // renderer
} // engine
