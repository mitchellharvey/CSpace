// File:        resources/PrimitiveLoader.h
// Author:      Mitchell Harvey
// Date:        2/2/2012
// 

#ifndef ENGINE_RESOURCES_PRIMITIVELOADER_H_
#define ENGINE_RESOURCES_PRIMITIVELOADER_H_

#include "resources/ModelLoader.h"
#include "math/vector.h"

namespace engine {
namespace resources {

class PrimitiveLoader : public ModelLoader
{
public:
    enum PRIMITIVE
    {
        RECTANGLE,
        TRIANGLE,
        CIRCLE,
        CUBE,
        PYRAMID,
        SPHERE
    };

    PrimitiveLoader(const PRIMITIVE type);
    virtual ~PrimitiveLoader();

    virtual bool LoadModel(const system::utf8 &filename);

    virtual void UnloadModel();

protected:
    PrimitiveLoader(const PrimitiveLoader &);

    virtual void CopyData(const math::vector3 *vertices, const math::vector3 *normals, const system::UINT32 *indices, const math::vector2 *uvs,
                          system::UINT32 vertexCount, system::UINT32 normalCount, system::UINT32 indexCount, system::UINT32 uvCount);

    PRIMITIVE _type;
    
};
} // resources
} // engine
#endif // ENGINE_RESOURCES_PRIMITIVELOADER_H_
