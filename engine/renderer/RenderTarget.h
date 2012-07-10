// File:        renderer/RendererTarget.h
// Author:      Mitchell Harvey
// Date:        8/31/2011
// 

#ifndef ENGINE_RENDERER_RENDERTARGET_H_
#define ENGINE_RENDERER_RENDERTARGET_H_

namespace engine {
namespace renderer {

class RenderTarget
{
friend class Renderer;
public:
    RenderTarget(void) { };
    virtual ~RenderTarget(void) { };

protected:
    virtual void EnableRenderTarget(void) = 0;
    virtual void DisableRenderTarget(void) = 0;
};
} // renderer
} // engine
#endif // ENGINE_RENDERER_RENDERTARGET_H_
