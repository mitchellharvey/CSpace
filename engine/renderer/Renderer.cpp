// File:        renderer/Renderer.cpp
// Author:      Mitchell Harvey
// Date:        8/31/2011
// 

#include "renderer/Renderer.h"
#include "renderer/RenderTarget.h"
#include "renderer/Scene.h"

namespace engine {
namespace renderer {

Renderer::Renderer(void)
{
}
//------------------------------------------------------------------------------------------------------------------------
Renderer::~Renderer(void)
{
}
//------------------------------------------------------------------------------------------------------------------------
bool Renderer::Initialize(void)
{
    return ImplementationInitialize();
}
//------------------------------------------------------------------------------------------------------------------------
void Renderer::UpdateViewPort(system::INT32 x, system::INT32 y, system::UINT32 width, system::UINT32 height)
{
}
//------------------------------------------------------------------------------------------------------------------------
void Renderer::RenderScene(RenderTarget *pTarget, Camera *pCamera, Scene *pScene)
{
    pTarget->EnableRenderTarget();

    ImplementationRenderScene(pCamera, pScene);

    pTarget->DisableRenderTarget();
}

} // renderer
} // engine
