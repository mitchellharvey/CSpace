// File:        resources/ModelLoader.cpp
// Author:      Mitchell Harvey
// Date:        2/2/2012
// 

#include <memory>

#include "resources/ModelLoader.h"

using namespace engine::math;

namespace engine {
namespace resources {

ModelLoader::ModelLoader() :
 _vertices(0)
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
ModelLoader::~ModelLoader()
{
}
//------------------------------------------------------------------------------------------------------------------------
const vector3 * const ModelLoader::GetVertices() const
{
    return _vertices;
}
//------------------------------------------------------------------------------------------------------------------------
const system::UINT32 * const ModelLoader::GetIndices() const
{
    return _indices;
}
//------------------------------------------------------------------------------------------------------------------------
const vector2 * const ModelLoader::GetUVs() const
{
    return _uvs;
}
//------------------------------------------------------------------------------------------------------------------------
const vector3 * const ModelLoader::GetNormals() const
{
    return _normals;
}
//------------------------------------------------------------------------------------------------------------------------
const vector4 * const ModelLoader::GetColors() const
{
    return _colors;
}
//------------------------------------------------------------------------------------------------------------------------
system::UINT32 ModelLoader::GetVertexCount() const
{
    return _vertexCount;
}
//------------------------------------------------------------------------------------------------------------------------
system::UINT32 ModelLoader::GetIndexCount() const
{
    return _indexCount;
}
//------------------------------------------------------------------------------------------------------------------------
system::UINT32 ModelLoader::GetUVCount() const
{
    return _uvCount;
}
//------------------------------------------------------------------------------------------------------------------------
system::UINT32 ModelLoader::GetNormalCount() const
{
    return _normalCount;
}
//------------------------------------------------------------------------------------------------------------------------
system::UINT32 ModelLoader::GetColorCount() const
{
    return _colorCount;
}
} // resources
} // engine
