// File:        renderer/RenderContext.h
// Author:      Mitchell Harvey
// Date:        6/14/2011
// 

#ifndef ENGINE_RENDERER_RENDERCONTEXT_H_
#define ENGINE_RENDERER_RENDERCONTEXT_H_

#include "system/types.h"

using namespace engine::system;

namespace engine {
namespace renderer {

class RenderContext
{
public:
    void Bind(void *pDrawContext) ;
    void Unbind(void *pDrawContext);

protected:
    RenderContext(void);
    RenderContext(const RenderContext &) { }
    virtual ~RenderContext(void);

    virtual void ImplementationBind(void *pDrawContext) = 0;
    virtual void ImplementationUnbind(void *pDrawContext) = 0;
private:

};
} // renderer
} // engine
#endif // ENGINE_RENDERER_RENDERCONTEXT_H_
