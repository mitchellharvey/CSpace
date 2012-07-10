// File:        renderer/Renderable.cpp
// Author:      Mitchell Harvey
// Date:        4/5/2012
// 

#include "renderer/Renderable.h"

namespace engine {
namespace renderer {

Renderable::Renderable(void) :
 _modelResource(0)
,_parent(0)
{
}
//------------------------------------------------------------------------------------------------------------------------
Renderable::~Renderable(void)
{
}
//------------------------------------------------------------------------------------------------------------------------
Material &Renderable::GetMaterial(void)
{
    return _material;
}
//------------------------------------------------------------------------------------------------------------------------
ModelResource *Renderable::GetModelResource(void) const
{
    return _modelResource;
}
//------------------------------------------------------------------------------------------------------------------------
Renderable *Renderable::GetParent(void) const
{
    return _parent;
}
//------------------------------------------------------------------------------------------------------------------------
matrix4x4 Renderable::GetWorldTransform(void) const
{
    if (_parent)
    {
        return (_parent->GetWorldTransform() * _transform);
    }

    return _transform;
}
//------------------------------------------------------------------------------------------------------------------------
void Renderable::SetMaterial(const Material &material)
{
    _material = material;
}
//------------------------------------------------------------------------------------------------------------------------
void Renderable::SetModelResource(ModelResource *modelResource)
{
    _modelResource = modelResource;
}
//------------------------------------------------------------------------------------------------------------------------
void Renderable::SetParent(Renderable *parent)
{
    _parent = parent;
}

} // renderer
} // engine
