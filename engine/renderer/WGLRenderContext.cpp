// File:        renderer/WGLRenderContext.cpp
// Author:      Mitchell Harvey
// Date:        6/14/2011
// 

#include "renderer/WGLRenderContext.h"
#include "renderer/Window.h"

#include <gl/GL.h>
#include <gl/GLU.h>

namespace engine {
namespace renderer {

//------------------------------------------------------------------------------------------------------------------------
WGLRenderContext::WGLRenderContext(HGLRC hGLRC) :
 _hGLRC(hGLRC)
{

}
//------------------------------------------------------------------------------------------------------------------------
WGLRenderContext::~WGLRenderContext(void)
{
}
//------------------------------------------------------------------------------------------------------------------------
void WGLRenderContext::ImplementationBind(void *pDrawContext)
{
    wglMakeCurrent(static_cast<HDC>(pDrawContext), _hGLRC);
}
//------------------------------------------------------------------------------------------------------------------------
void WGLRenderContext::ImplementationUnbind(void *pDrawContext)
{
    wglMakeCurrent(static_cast<HDC>(pDrawContext), 0);
}
} // renderer
} // engine
