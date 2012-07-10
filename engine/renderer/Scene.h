// File:        renderer/Scene.h
// Author:      Mitchell Harvey
// Date:        8/31/2011
// 
#ifndef ENGINE_RENDERER_SCENE_H_
#define ENGINE_RENDERER_SCENE_H_

#include <vector>
#include "renderer/Renderable.h"

namespace engine {
namespace renderer {

class Scene
{
public:
    Scene(void);
    virtual ~Scene(void);

    virtual void AddRenderable(Renderable *renderable);
    virtual void RemoveRenderable(Renderable *renderable);
    virtual void ClearRenderables(void);

    virtual void GetSortedRenderables(std::vector<Renderable> &sorted) const;

protected:
    std::vector<Renderable *> _renderables;

};
} // renderer
} // engine
#endif // ENGINE_RENDERER_SCENE_H_
