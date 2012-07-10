// File:        resources/ModelResource.h
// Author:      Mitchell Harvey
// Date:        2/2/2012
// 

#ifndef ENGINE_RESOURCES_MODELRESOURCE_H_
#define ENGINE_RESOURCES_MODELRESOURCE_H_

#include "resources/Resource.h"
#include "math/vector.h"

namespace engine {
namespace resources {

class ModelResource : public Resource
{
friend class ResourceLoader;
public:
    virtual Resource::TYPE GetType(void) const;

    const math::vector3 * const GetVertices(void) const;
    system::UINT32 GetTotalVertices(void) const;
    const math::vector4 * const GetColors(void) const;
    system::UINT32 GetTotalColors(void) const;
    const system::UINT32 * const GetIndices(void) const;
    system::UINT32 GetTotalIndices(void) const;

private:
    ModelResource(const system::utf8 &resoureFile);
    ModelResource(const ModelResource &c) : Resource(_resourceFile) {}
    virtual ~ModelResource();

    math::vector3 *_vertices;
    system::UINT32 *_indices;
    math::vector2 *_uvs;
    math::vector3 *_normals;
    math::vector4 *_colors;

    system::UINT32 _vertexCount;
    system::UINT32 _indexCount;
    system::UINT32 _uvCount;
    system::UINT32 _normalCount;
    system::UINT32 _colorCount;
};
} // resources
} // engine
#endif // ENGINE_RESOURCES_MODELRESOURCE_H_
