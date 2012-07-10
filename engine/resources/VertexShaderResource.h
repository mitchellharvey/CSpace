// File:        resources/VertexShaderResource.h
// Author:      Mitchell Harvey
// Date:        4/7/2012
// 

#ifndef ENGINE_RESOURCES_VERTEXSHADERRESOURCE_H_
#define ENGINE_RESOURCES_VERTEXSHADERRESOURCE_H_

#include "resources/Resource.h"

namespace engine {
namespace resources {

class VertexShaderResource : public Resource
{
friend class ResourceLoader;
public:
    virtual Resource::TYPE GetType() const;

    char * const GetSource(void) const;
    system::UINT32 GetSourceByteSize(void) const;

    void SetVertexAttribName(const char *name);
    void SetColorAttribName(const char *name);
    void SetNormalAttribName(const char *name);

    char * const GetVertexAttribName(void) const;
    char * const GetColorAttribName(void) const;
    char * const GetNormalAttribName(void) const;

private:
    VertexShaderResource(const system::utf8 &resoureFile);
    VertexShaderResource(const VertexShaderResource &c) : Resource(_resourceFile) {}
    virtual ~VertexShaderResource();
    
    char *_shaderSource;
    system::UINT32 _shaderSourceByteSize;
    char _vertexAttribName[256];
    char _colorAttribName[256];
    char _normalAttribName[256];
};
} // resources
} // engine
#endif // ENGINE_RESOURCES_VERTEXSHADERRESOURCE_H_

