// File:        resources/ModelResource.cpp
// Author:      Mitchell Harvey
// Date:        2/2/2012
// 

#include "resources/ModelResource.h"

namespace engine {
namespace resources {

ModelResource::ModelResource(const system::utf8 &resourceFile) :
 Resource(resourceFile)
,_vertices(0)
,_indices(0)
,_uvs(0)
,_normals(0)
,_colors(0)
,_vertexCount(0)
,_indexCount(0)
,_uvCount(0)
,_normalCount(0)
,_colorCount(0)
{
}
//------------------------------------------------------------------------------------------------------------------------
ModelResource::~ModelResource()
{
}
//------------------------------------------------------------------------------------------------------------------------
Resource::TYPE ModelResource::GetType() const
{
    return Resource::MODEL;
}
//------------------------------------------------------------------------------------------------------------------------
const math::vector3 * const ModelResource::GetVertices(void) const
{
    return _vertices;
}
//------------------------------------------------------------------------------------------------------------------------
system::UINT32 ModelResource::GetTotalVertices(void) const
{
    return _vertexCount;
}
//------------------------------------------------------------------------------------------------------------------------
const system::UINT32 * const ModelResource::GetIndices(void) const
{
    return _indices;
}
//------------------------------------------------------------------------------------------------------------------------
system::UINT32 ModelResource::GetTotalIndices(void) const
{
    return _indexCount;
}
//------------------------------------------------------------------------------------------------------------------------
const math::vector4 * const ModelResource::GetColors(void) const
{
    return _colors;
}
//------------------------------------------------------------------------------------------------------------------------
system::UINT32 ModelResource::GetTotalColors(void) const
{
    return _colorCount;
}
} // resources
} // engine
