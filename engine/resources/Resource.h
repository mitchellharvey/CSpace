// File:        resources/Resource.h
// Author:      Mitchell Harvey
// Date:        1/24/2012
// 

#ifndef ENGINE_RESOURCES_RESOURCE_H_
#define ENGINE_RESOURCES_RESOURCE_H_

#include "system/types.h"
#include "system/utf8.h"

namespace engine {
namespace resources {

class ResourceLoader;

class Resource
{
public:
    enum TYPE
    {
        TEXTURE,
        MODEL,
        VERTEX_SHADER,
        FRAGMENT_SHADER,
        GEOMETRY_SHADER,
    };

    const system::utf8 &GetResourceFile() const;

    virtual TYPE GetType() const = 0;

protected:
    Resource(const system::utf8 &resourceFile);
    Resource(const Resource &) {}
    virtual ~Resource();

    system::utf8    _resourceFile;

};
} // resources
} // engine
#endif // ENGINE_RESOURCES_RESOURCE_H_
