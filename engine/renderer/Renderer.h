// File:        renderer/Renderer.h
// Author:      Mitchell Harvey
// Date:        8/31/2011
// 

#include "system/types.h"

#ifndef ENGINE_RENDERER_RENDERER_H_
#define ENGINE_RENDERER_RENDERER_H_

namespace engine {
namespace renderer {

class RenderTarget;
class Scene;
class Camera;

class Renderer
{
public:
    // TODO: Create settings structure for initialization
    bool Initialize(void);

    void UpdateViewPort(system::INT32 x, system::INT32 y, system::UINT32 width, system::UINT32 height);
    void RenderScene(RenderTarget *pTarget, Camera *pCamera, Scene *pScene);

protected:
    Renderer(void);
    Renderer(const Renderer &) { }
    virtual ~Renderer(void);

    virtual void ImplementationRenderScene(Camera *pCamera, Scene *pScene) = 0;
    virtual bool ImplementationInitialize(void) = 0;
    virtual void ImplementationUpdateViewport(system::INT32 x, system::INT32 y, system::UINT32 width, system::UINT32 height) = 0;

};

Renderer *CreateNewRenderer(void);
void DestroyRenderer(Renderer *pRenderer);

} // renderer
} // engine
#endif // ENGINE_RENDERER_RENDERER_H_
