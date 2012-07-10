// File:        resources/GLSLLoader.cpp
// Author:      Mitchell Harvey
// Date:        4/7/2012
// 

#include <memory>
#include "system/io.h"
#include "resources/GLSLLoader.h"

namespace engine {
namespace resources {

GLSLLoader::GLSLLoader() :
 ShaderLoader()
{
}
//------------------------------------------------------------------------------------------------------------------------
GLSLLoader::~GLSLLoader()
{
}
bool GLSLLoader::LoadShader(const system::utf8 &filename)
{
    UnloadShader();

    system::utf8 shaderSource;
    system::IORESULT res = system::ReadFileText(filename, shaderSource);
    if (res == system::IO_OK)
    {
        _shaderSourceByteSize = shaderSource.size() + 1;
        _shaderSource = new char[_shaderSourceByteSize];
        memset(_shaderSource, 0, _shaderSourceByteSize);

        memcpy(_shaderSource, shaderSource.c_str(), _shaderSourceByteSize);

        return true;
    }

    return false;
}
//------------------------------------------------------------------------------------------------------------------------
void GLSLLoader::UnloadShader()
{
    delete [] _shaderSource;
    _shaderSourceByteSize = 0;
    _shaderSource = 0;
}
//------------------------------------------------------------------------------------------------------------------------
} // resources
} // engine


