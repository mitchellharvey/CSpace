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

private:
    PrimitiveLoader(const PrimitiveLoader &);

    void CreateTriangle(void);
    void CreateCube(void);

    PRIMITIVE _type;
    
};
} // resources
} // engine
#endif // ENGINE_RESOURCES_PRIMITIVELOADER_H_
