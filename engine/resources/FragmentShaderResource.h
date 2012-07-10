// File:        resources/FragmentShaderResource.h
// Author:      Mitchell Harvey
// Date:        4/8/2012
// 

#ifndef ENGINE_RESOURCES_FRAGMENTSHADERRESOURCE_H_
#define ENGINE_RESOURCES_FRAGMENTSHADERRESOURCE_H_

#include "resources/Resource.h"

namespace engine {
namespace resources {

class FragmentShaderResource : public Resource
{
friend class ResourceLoader;
public:
    virtual Resource::TYPE GetType() const;

    char * const GetSource(void) const;
    system::UINT32 GetSourceByteSize(void) const;

private:
    FragmentShaderResource(const system::utf8 &resoureFile);
    FragmentShaderResource(const FragmentShaderResource &c) : Resource(_resourceFile) {}
    virtual ~FragmentShaderResource();
    
    char *_shaderSource;
    system::UINT32 _shaderSourceByteSize;
};
} // resources
} // engine
#endif // ENGINE_RESOURCES_FRAGMENTSHADERRESOURCE_H_


