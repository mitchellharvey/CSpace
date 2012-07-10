// File:        resources/ShaderLoader.cpp
// Author:      Mitchell Harvey
// Date:        4/7/2012
// 

#include "resources/ShaderLoader.h"

namespace engine {
namespace resources {

ShaderLoader::ShaderLoader() :
 _shaderSource(0)
,_shaderSourceByteSize(0)
{
}
//------------------------------------------------------------------------------------------------------------------------
ShaderLoader::~ShaderLoader()
{
}
//------------------------------------------------------------------------------------------------------------------------
const char * const ShaderLoader::GetShaderSource() const
{
    return _shaderSource;
}
//------------------------------------------------------------------------------------------------------------------------
system::UINT32 ShaderLoader::GetShaderSourceSize() const
{
    return _shaderSourceByteSize;
}
//------------------------------------------------------------------------------------------------------------------------
} // resources
} // engine

