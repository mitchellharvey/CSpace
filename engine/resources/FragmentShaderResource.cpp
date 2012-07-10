// File:        resources/FragmentShaderResource.cpp
// Author:      Mitchell Harvey
// Date:        4/8/2012
// 

#include "resources/FragmentShaderResource.h"

namespace engine {
namespace resources {

FragmentShaderResource::FragmentShaderResource(const system::utf8 &resourceFile) :
 Resource(resourceFile)
,_shaderSource(0)
,_shaderSourceByteSize(0)
{
}
//------------------------------------------------------------------------------------------------------------------------
FragmentShaderResource::~FragmentShaderResource()
{
}
//------------------------------------------------------------------------------------------------------------------------
Resource::TYPE FragmentShaderResource::GetType() const
{
    return Resource::FRAGMENT_SHADER;
}
//------------------------------------------------------------------------------------------------------------------------
char * const FragmentShaderResource::GetSource(void) const
{
    return _shaderSource;
}
//------------------------------------------------------------------------------------------------------------------------
system::UINT32 FragmentShaderResource::GetSourceByteSize(void) const
{
    return _shaderSourceByteSize;
}
} // resources
} // engine

