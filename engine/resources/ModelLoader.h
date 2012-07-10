// File:        resources/ModelLoader.h
// Author:      Mitchell Harvey
// Date:        2/2/2012
// 

#ifndef ENGINE_RESOURCES_MODELLOADER_H_
#define ENGINE_RESOURCES_MODELLOADER_H_

#include "system/types.h"
#include "system/utf8.h"
#include "math/vector.h"

namespace engine {
namespace resources {

class ModelLoader
{
public:
    ModelLoader();
    virtual ~ModelLoader();

    virtual bool LoadModel(const system::utf8 &filename) = 0;
    virtual void UnloadModel() = 0;

    virtual const math::vector3 * const GetVertices() const;
    virtual const system::UINT32 * const GetIndices() const;
    virtual const math::vector2 * const GetUVs() const;
    virtual const math::vector3 * const GetNormals() const;
    virtual const math::vector4 * const GetColors() const;

    virtual system::UINT32 GetVertexCount() const;
    virtual system::UINT32 GetIndexCount() const;
    virtual system::UINT32 GetUVCount() const;
    virtual system::UINT32 GetNormalCount() const;
    virtual system::UINT32 GetColorCount() const;

protected:
    ModelLoader(const ModelLoader &);
    
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
#endif // ENGINE_RESOURCES_MODELLOADER_H_
