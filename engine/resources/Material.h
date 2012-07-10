// File:        resources/Material.h
// Author:      Mitchell Harvey
// Date:        4/5/2012
// 

#ifndef ENGINE_RESOURCES_MATERIAL_H_
#define ENGINE_RESOURCES_MATERIAL_H_

namespace engine {
namespace resources {

class TextureResource;
class VertexShaderResource;
class FragmentShaderResource;

class Material
{
public:
    Material(void);
    ~Material(void);

    void SetTexture(TextureResource *texture);
    void SetVertexShader(VertexShaderResource *vertexShader);
    void SetFragmentShader(FragmentShaderResource *fragmentShader);

    TextureResource *GetTexture(void) const;
    VertexShaderResource *GetVertexShader(void) const;
    FragmentShaderResource *GetFragmentShader(void) const;

    void SetProjectionMatrixShaderVar(const char *name);
    void SetModelViewMatrixShaderVar(const char *name);

    char * const GetProjectionMatrixShaderVar(void) const;
    char * const GetModelViewMatrixShaderVar(void) const;

protected:
    TextureResource *_texture;
    VertexShaderResource *_vertexShader;
    FragmentShaderResource *_fragmentShader;
    char _projectionMatrixShaderVar[256];
    char _modelViewMatrixShaderVar[256];
};
} // resources
} // engine
#endif // ENGINE_RESOURCES_MATERIAL_H_
