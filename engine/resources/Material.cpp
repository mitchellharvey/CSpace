// File:        resources/Material.cpp
// Author:      Mitchell Harvey
// Date:        4/8/2012
// 

#include <string.h>
#include "resources/Material.h"

namespace engine {
namespace resources {

Material::Material(void) :
 _texture(0)
,_vertexShader(0)
,_fragmentShader(0)
{
    memset(_projectionMatrixShaderVar, 0, sizeof(_projectionMatrixShaderVar));
    memset(_modelViewMatrixShaderVar, 0, sizeof(_modelViewMatrixShaderVar));
}
//------------------------------------------------------------------------------------------------------------------------
Material::~Material(void)
{
}
//------------------------------------------------------------------------------------------------------------------------
void Material::SetTexture(TextureResource *texture)
{
    _texture = texture;
}
//------------------------------------------------------------------------------------------------------------------------
void Material::SetVertexShader(VertexShaderResource *vertexShader)
{
    _vertexShader = vertexShader;
}
//------------------------------------------------------------------------------------------------------------------------
void Material::SetFragmentShader(FragmentShaderResource *fragmentShader)
{
    _fragmentShader = fragmentShader;
}
//------------------------------------------------------------------------------------------------------------------------
TextureResource *Material::GetTexture(void) const
{
    return _texture;
}
//------------------------------------------------------------------------------------------------------------------------
VertexShaderResource *Material::GetVertexShader(void) const
{
    return _vertexShader;
}
//------------------------------------------------------------------------------------------------------------------------
FragmentShaderResource *Material::GetFragmentShader(void) const
{
    return _fragmentShader;
}
//------------------------------------------------------------------------------------------------------------------------
void Material::SetProjectionMatrixShaderVar(const char *name)
{
    strncpy_s(_projectionMatrixShaderVar, name, 255);
}
//------------------------------------------------------------------------------------------------------------------------
void Material::SetModelViewMatrixShaderVar(const char *name)
{
    strncpy_s(_modelViewMatrixShaderVar, name, 255);
}
//------------------------------------------------------------------------------------------------------------------------
char * const Material::GetProjectionMatrixShaderVar(void) const
{
    return (char * const)_projectionMatrixShaderVar;
}
//------------------------------------------------------------------------------------------------------------------------
char * const Material::GetModelViewMatrixShaderVar(void) const
{
    return (char * const)_modelViewMatrixShaderVar;
}
} // resources
} // engine
