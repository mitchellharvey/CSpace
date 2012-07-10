// File:        renderer/Renderable.h
// Author:      Mitchell Harvey
// Date:        4/5/2012
// 

#ifndef ENGINE_RENDERER_RENDERABLE_H_
#define ENGINE_RENDERER_RENDERABLE_H_

#include "renderer/Transform.h"
#include "resources/ModelResource.h"
#include "resources/Material.h"

using engine::resources::ModelResource;
using engine::resources::Material;

namespace engine {
namespace renderer {

class Renderable : public Transform
{
public:
    // TODO: Write a copy constructor for this.  Renderable's and all objects within
    // should be copyable.  keep in mind, resource pointers never change :)
    Renderable(void);
    virtual ~Renderable(void);

    Material &GetMaterial(void);
    ModelResource *GetModelResource(void) const;
    Renderable *GetParent(void) const;
    matrix4x4 GetWorldTransform(void) const; 

    void SetMaterial(const Material &material);
    void SetModelResource(ModelResource *modelResource);
    void SetParent(Renderable *parent);

protected:
    Material _material;
    ModelResource *_modelResource;
    Renderable *_parent;
};
} // renderer
} // engine
#endif // ENGINE_RENDERER_RENDERABLE_H_
