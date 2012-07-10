// File:        renderer/WGLRenderContext.h
// Author:      Mitchell Harvey
// Date:        6/14/2011
// 

#ifndef ENGINE_RENDERER_WGLRENDERCONTEXT_H_
#define ENGINE_RENDERER_WGLRENDERCONTEXT_H_

#include <Windows.h>

#include "renderer/RenderContext.h"

using namespace engine::system;

namespace engine {
namespace renderer {

class Window;

class WGLRenderContext : public RenderContext
{
friend Window *CreateNewWindow(void);
friend void DestroyWindow(Window *pWindow);

protected:
    void ImplementationBind(void *pDrawContext);
    void ImplementationUnbind(void *pDrawContext);

private:
    WGLRenderContext(HGLRC hGLRC);
    WGLRenderContext(const WGLRenderContext &) { }
    virtual ~WGLRenderContext(void);

    HGLRC _hGLRC;

};
} // renderer
} // engine
#endif // ENGINE_RENDERER_WGLRENDERCONTEXT_H_
