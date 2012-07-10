// File:        resources/ShaderLoader.h
// Author:      Mitchell Harvey
// Date:        4/7/2012
// 

#ifndef ENGINE_RESOURCES_SHADERLOADER_H_
#define ENGINE_RESOURCES_SHADERLOADER_H_

#include "system/utf8.h"
#include "system/types.h"

namespace engine {
namespace resources {

class ShaderLoader
{
public:
    ShaderLoader();
    virtual ~ShaderLoader();

    virtual bool LoadShader(const system::utf8 &filename) = 0;
    virtual void UnloadShader() = 0;

    virtual const char * const GetShaderSource() const;

    virtual system::UINT32 GetShaderSourceSize() const;

protected:
    ShaderLoader(const ShaderLoader &);
    
    char *_shaderSource;
    system::UINT32 _shaderSourceByteSize;
    
};
} // resources
} // engine
#endif // ENGINE_RESOURCES_SHADERLOADER_H_

