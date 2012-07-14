// File:        renderer/Transform.h
// Author:      Mitchell Harvey
// Date:        6/26/2011
// 

#ifndef ENGINE_RENDERER_TRANSFORM_H_
#define ENGINE_RENDERER_TRANSFORM_H_

#include "math/matrix.h"
#include "math/vector.h"

namespace engine {
namespace renderer {

using namespace math;

class Transform
{
public:
    Transform(void);
    Transform(const Transform &c);
    Transform(const matrix4x4 &m);
    Transform(const matrix3x3 &m);
    virtual ~Transform(void);

    vector3 GetTranslation(void) const;
    vector3 GetXAxis(void) const;
    vector3 GetYAxis(void) const;
    vector3 GetZAxis(void) const;

    void SetTranslation(float x, float y, float z);
    void SetTranslation(const vector3 &t);
    void SetXAxis(float x, float y, float z);
    void SetXAxis(const vector3 &v);
    void SetYAxis(float x, float y, float z);
    void SetYAxis(const vector3 &v);
    void SetZAxis(float x, float y, float z);
    void SetZAxis(const vector3 &v);
    
    void ScaleXAxis(float s);
    void ScaleYAxis(float s);
    void ScaleZAxis(float s);

    void RotateOnX(float radians);
    void RotateOnY(float radians);
    void RotateOnZ(float radians);

    void LookAt(const vector3 &p);
    void LookAt(float x, float y, float z);

    matrix4x4 &GetTransformMatrix(void);

protected:
    matrix4x4 _transform;

};
} // renderer
} // engine
#endif // ENGINE_RENDERER_TRANSFORM_H_
