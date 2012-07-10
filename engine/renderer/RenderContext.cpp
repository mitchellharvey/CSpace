// File:        renderer/RenderContext.cpp
// Author:      Mitchell Harvey
// Date:        6/14/2011
// 

#include "renderer/RenderContext.h"

namespace engine {
namespace renderer {

RenderContext::RenderContext(void)
{
}
//------------------------------------------------------------------------------------------------------------------------
RenderContext::~RenderContext(void)
{
}
//------------------------------------------------------------------------------------------------------------------------
void RenderContext::Bind(void *pDrawContext)
{
    ImplementationBind(pDrawContext);
}
//------------------------------------------------------------------------------------------------------------------------
void RenderContext::Unbind(void *pDrawContext)
{
    ImplementationUnbind(pDrawContext);
}
} // renderer
} // engine
