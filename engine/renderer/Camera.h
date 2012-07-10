// File:        renderer/Camera.h
// Author:      Mitchell Harvey
// Date:        6/26/2011
// 

#ifndef ENGINE_RENDERER_CAMERA_H_
#define ENGINE_RENDERER_CAMERA_H_

#include "renderer/Transform.h"
#include "math/matrix.h"

namespace engine {
namespace renderer {

class Camera : public Transform
{
public:
    Camera(void);
    virtual ~Camera(void);

    void SetFieldOfView(float fov);
    void SetWidthHeightRatio(float ration);
    void SetNearPlaneDistance(float near);
    void SetFarPlaneDistance(float far);

    float GetFieldOfView(void) const;
    float GetWidthHeightRatio(void) const;
    float GetNearPlaneDistance(void) const;
    float GetFarPlaneDistance(void) const;

    // TODO: Remember, everything is only column order
    // because that's how I chose to put the data into the matrices
    // all this shit is setup column order!
    virtual matrix4x4 GetProjectionMatrix(void) const;
    virtual matrix4x4 GetViewMatrix(void) const;

protected:
    float _fieldOfView;
    float _widthHeightRatio;
    float _nearPlane;
    float _farPlane;

};
} // renderer
} // engine
#endif // ENGINE_RENDERER_CAMERA_H_
