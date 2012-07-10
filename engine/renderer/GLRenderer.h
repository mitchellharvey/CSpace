// File:        renderer/GLRenderer.h
// Author:      Mitchell Harvey
// Date:        8/31/2011
// 

#include <unordered_map>

#include "renderer/Renderer.h"
#include "resources/ModelResource.h"
#include "resources/VertexShaderResource.h"
#include "resources/FragmentShaderResource.h"
#include "resources/Material.h"

#ifndef ENGINE_RENDERER_GLRENDERER_H_
#define ENGINE_RENDERER_GLRENDERER_H_

using engine::resources::ModelResource;
using engine::resources::VertexShaderResource;
using engine::resources::FragmentShaderResource;
using engine::resources::Material;

namespace engine {
namespace renderer {

class Renderable;

class GLRenderer : Renderer
{
friend Renderer *CreateNewRenderer(void);
friend void DestroyRenderer(Renderer *pRenderer);

// MMH LEFT OFF:
// Basically GL specific stuff, like VBO index and what not, for each resource,
// should be it's own small information structure
// Then we will use resource pointer as index for the individual struct for each thing
// we know resource addresses will never change, so we determine the type once then
// we always have implmentation information specific too it ready to be set or read
// use that to do the VBO and VBA management
//
private:
    struct GLDataBuffer
    {
        system::UINT32 id;
        system::UINT32 usedSize;
        system::UINT32 totalSize;
    };

    struct ModelResourceData
    {
        system::UINT32 vertexOffset;
        system::UINT32 vertexCount;

        system::UINT32 colorOffset;
        system::UINT32 colorCount;

        system::UINT32 indexOffset;
        system::UINT32 indexCount;
    };

    struct VertexShaderResourceData
    {
        system::UINT32 id;
        bool compiled;
    };

    struct FragmentShaderResourceData
    {
        system::UINT32 id;
        bool compiled;
    };

    struct ShaderProgram
    {
        system::UINT32 id;
        VertexShaderResourceData *vertexShader;
        FragmentShaderResourceData *fragmentShader;
        system::INT32 vertexAttribLoc;
        system::INT32 normalAttribLoc;
        system::INT32 colorAttribLoc;
        system::INT32 projMatrixAttribLoc;
        system::INT32 modelViewMatrixAttribLoc;
        bool linked;
    };

    GLRenderer(void);
    GLRenderer(const GLRenderer &) { }
    ~GLRenderer(void);

    ModelResourceData &PushToGPU(ModelResource *resource);
    void RenderModel(ModelResourceData &data);

    void ApplyMaterial(Material &material, Camera *camera, Renderable *renderable);

    VertexShaderResourceData &CompileShader(VertexShaderResource *resource);
    FragmentShaderResourceData &CompileShader(FragmentShaderResource *resource);
    ShaderProgram &LinkShaderProgram(VertexShaderResource *vertShader, FragmentShaderResource *fragShader);

    void ImplementationRenderScene(Camera *pCamera, Scene *pScene);
    bool ImplementationInitialize(void);
    void ImplementationUpdateViewport(system::INT32 x, system::INT32 y, system::UINT32 width, system::UINT32 height);

    bool _initialized;
    system::UINT32 *_glVertexArrays;
    system::INT32 _glTotalVertexArrays;
    GLDataBuffer _staticVertexBuffer;
    GLDataBuffer _staticIndexBuffer;
    GLDataBuffer _staticColorBuffer;
    VertexShaderResource *_defaultVertexShader;
    FragmentShaderResource *_defaultFragmentShader;

    typedef std::unordered_map<ModelResource *, ModelResourceData, std::hash<ModelResource *>> ResourceToModelDataMap;
    typedef std::pair<ModelResource *, ModelResourceData> ResourceToModelDataPair;
    ResourceToModelDataMap _modelResourceDataMap;

    typedef std::unordered_map<VertexShaderResource *, VertexShaderResourceData, std::hash<VertexShaderResource *>> ResourceToVertexShaderDataMap;
    typedef std::pair<VertexShaderResource *, VertexShaderResourceData> ResourceToVertexShaderDataPair;
    ResourceToVertexShaderDataMap _vertexShaderResourceDataMap;

    typedef std::unordered_map<FragmentShaderResource *, FragmentShaderResourceData, std::hash<FragmentShaderResource *>> ResourceToFragmentShaderDataMap;
    typedef std::pair<FragmentShaderResource *, FragmentShaderResourceData> ResourceToFragmentShaderDataPair;
    ResourceToFragmentShaderDataMap _fragmentShaderResourceDataMap;

    typedef std::list<ShaderProgram> ShaderProgramList;
    ShaderProgramList _shaderProgramList;

};
} // renderer
} // engine
#endif // ENGINE_RENDERER_GLRENDERER_H_
