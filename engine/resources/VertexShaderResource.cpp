// File:        resources/VertexShaderResource.cpp
// Author:      Mitchell Harvey
// Date:        4/7/2012
// 

#include "resources/VertexShaderResource.h"

namespace engine {
namespace resources {

VertexShaderResource::VertexShaderResource(const system::utf8 &resourceFile) :
 Resource(resourceFile)
,_shaderSource(0)
,_shaderSourceByteSize(0)
{
    memset(_vertexAttribName, 0, 256);
    memset(_colorAttribName, 0, 256);
    memset(_normalAttribName, 0, 256);
}
//------------------------------------------------------------------------------------------------------------------------
VertexShaderResource::~VertexShaderResource()
{
}
//------------------------------------------------------------------------------------------------------------------------
Resource::TYPE VertexShaderResource::GetType() const
{
    return Resource::VERTEX_SHADER;
}
//------------------------------------------------------------------------------------------------------------------------
char * const VertexShaderResource::GetSource(void) const
{
    return _shaderSource;
}
//------------------------------------------------------------------------------------------------------------------------
system::UINT32 VertexShaderResource::GetSourceByteSize(void) const
{
    return _shaderSourceByteSize;
}
//------------------------------------------------------------------------------------------------------------------------
void VertexShaderResource::SetVertexAttribName(const char *name)
{
    strncpy_s(_vertexAttribName, name, 256);
}
//------------------------------------------------------------------------------------------------------------------------
void VertexShaderResource::SetColorAttribName(const char *name)
{
    strncpy_s(_colorAttribName, name, 256);
}
//------------------------------------------------------------------------------------------------------------------------
void VertexShaderResource::SetNormalAttribName(const char *name)
{
    strncpy_s(_normalAttribName, name, 256);
}
//------------------------------------------------------------------------------------------------------------------------
char * const VertexShaderResource::GetVertexAttribName(void) const
{
    return (char * const)_vertexAttribName;
}
//------------------------------------------------------------------------------------------------------------------------
char * const VertexShaderResource::GetColorAttribName(void) const
{
    return (char * const)_colorAttribName;
}
//------------------------------------------------------------------------------------------------------------------------
char * const VertexShaderResource::GetNormalAttribName(void) const
{
    return (char * const)_normalAttribName;
}
} // resources
} // engine
