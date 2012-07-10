// File:        resources/GLSLLoader.h
// Author:      Mitchell Harvey
// Date:        4/7/2012
// 

#ifndef ENGINE_RESOURCES_GLSLLOADER_H_
#define ENGINE_RESOURCES_GLSLLOADER_H_

#include "resources/ShaderLoader.h"

namespace engine {
namespace resources {

class GLSLLoader : public ShaderLoader
{
public:
    GLSLLoader();
    ~GLSLLoader();

    bool LoadShader(const system::utf8 &filename);
    void UnloadShader();

protected:
    GLSLLoader(const GLSLLoader &);
};
} // resources
} // engine
#endif // ENGINE_RESOURCES_SHADERLOADER_H_


