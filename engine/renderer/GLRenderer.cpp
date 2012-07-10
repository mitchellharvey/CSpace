// File:        renderer/GLRenderer.cpp
// Author:      Mitchell Harvey
// Date:        8/31/2011
// 

#include "GL/glew.h"
#include "GL/wglew.h"
#include "renderer/GLRenderer.h"
#include "renderer/Scene.h"
#include "resources/ResourceLoader.h"
#include "resources/GLSLLoader.h"
#include "renderer/Camera.h"

using engine::resources::ResourceLoader;
using engine::resources::GLSLLoader;

// TODO: Expose these so they can be tweaked
namespace {
    const engine::system::UINT32 cStaticVertexBufferSize = 1024 * 1024 * 50;
    const engine::system::UINT32 cStaticIndexBufferSize = 1024 * 1024 * 50;
}

namespace engine {
namespace renderer {

Renderer *CreateNewRenderer(void)
{
    return new GLRenderer();
}
//------------------------------------------------------------------------------------------------------------------------
void DestroyRenderer(Renderer *pRenderer)
{
    delete (GLRenderer *)pRenderer;
}
//------------------------------------------------------------------------------------------------------------------------
GLRenderer::GLRenderer(void) :
 _initialized(false)
,_glVertexArrays(0)
,_glTotalVertexArrays(0)
,_defaultVertexShader(0)
,_defaultFragmentShader(0)
{
}
//------------------------------------------------------------------------------------------------------------------------
GLRenderer::~GLRenderer(void)
{
    delete [] _glVertexArrays;
}
//------------------------------------------------------------------------------------------------------------------------
bool GLRenderer::ImplementationInitialize(void)
{
    if (_initialized)
    {
        return true;
    }

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    // Generate our vertex arrays
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &_glTotalVertexArrays);
    if (_glTotalVertexArrays >= 1)
    {
        _glVertexArrays = new system::UINT32[_glTotalVertexArrays];
        memset(_glVertexArrays, 0, sizeof(system::INT32) * _glTotalVertexArrays);

        glGenVertexArrays(_glTotalVertexArrays, _glVertexArrays);
    }
    else
    {
        // TODO: Log Error
        return false;
    }

    // Static Model Array Format
    glBindVertexArray(_glVertexArrays[0]);

    // Generate buffers

    // Vertex Buffer
    glGenBuffers(1, &_staticVertexBuffer.id);
    glBindBuffer(GL_ARRAY_BUFFER, _staticVertexBuffer.id);
    glBufferData(GL_ARRAY_BUFFER, cStaticVertexBufferSize, NULL, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    _staticVertexBuffer.usedSize = 0;
    _staticVertexBuffer.totalSize = cStaticVertexBufferSize;

    // Index Buffer
    glGenBuffers(1, &_staticIndexBuffer.id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _staticIndexBuffer.id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, cStaticIndexBufferSize, NULL, GL_STATIC_DRAW);

    _staticIndexBuffer.usedSize = 0;
    _staticIndexBuffer.totalSize = cStaticIndexBufferSize;

    glBindVertexArray(0);

    // Default engine resources
    _defaultVertexShader = ResourceLoader::LoadVertexShader("default.vert", GLSLLoader());
    _defaultFragmentShader = ResourceLoader::LoadFragmentShader("default.frag", GLSLLoader());

    _initialized = true;
    return _initialized;
}
//------------------------------------------------------------------------------------------------------------------------
void GLRenderer::ImplementationRenderScene(Camera *camera, Scene *pScene)
{
    std::vector<Renderable> renderables;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (pScene)
    {
        renderables.swap(pScene->GetSortedRenderables());
    }

    std::vector<Renderable>::iterator it = renderables.begin();
    std::vector<Renderable>::iterator end = renderables.end();
    for(; it != end; ++it)
    {
        Renderable &object = *it;
        Material mat = object.GetMaterial();

        ModelResourceData mdata = PushToGPU(object.GetModelResource());

        ApplyMaterial(mat, camera, &object);

        RenderModel(mdata);
    }
}
//------------------------------------------------------------------------------------------------------------------------
GLRenderer::ShaderProgram &GLRenderer::LinkShaderProgram(VertexShaderResource *vertShader, FragmentShaderResource *fragShader)
{
    VertexShaderResourceData &vertShaderData = CompileShader(vertShader);
    FragmentShaderResourceData &fragShaderData = CompileShader(fragShader); 

    ShaderProgramList::iterator it = _shaderProgramList.begin();
    ShaderProgramList::iterator end = _shaderProgramList.end();
    for(; it != end; ++it)
    {
        if (vertShader)
        {
            if (!it->vertexShader || (it->vertexShader->id != vertShaderData.id))
            {
                continue;
            }
        }

        if (fragShader)
        {
            if (!it->fragmentShader || (it->fragmentShader->id != fragShaderData.id))
            {
                continue;
            }
        }

        break;
    }

    ShaderProgram *program = 0;
    if (it != end)
    {
        program = &(*it);
    }
    else
    {
        // TODO: Add constructors/destructors to consolidate the initialize and cleanup 
        // code
        _shaderProgramList.push_back(ShaderProgram());
        program = &(_shaderProgramList.back());
        program->vertexShader = (vertShader) ? &vertShaderData : 0;
        program->fragmentShader = (fragShader) ? &fragShaderData : 0;
        program->vertexAttribLoc = -1;
        program->normalAttribLoc = -1;
        program->colorAttribLoc = -1;
        program->projMatrixAttribLoc = -1;
        program->modelViewMatrixAttribLoc = -1;
        program->id = glCreateProgram();
        program->linked = false;

        if (program->vertexShader)
        {
            glAttachShader(program->id, program->vertexShader->id);
        }

        if (program->fragmentShader)
        {
            glAttachShader(program->id, program->fragmentShader->id);
        }
    }

    if (!program->linked)
    {
        if (program->fragmentShader && !program->fragmentShader->compiled)
        {
            return *program;
        }

        if (program->vertexShader && !program->vertexShader->compiled)
        {
            return *program;
        }

        if (vertShader->GetVertexAttribName())
        {
            glBindAttribLocation(program->id, 0, vertShader->GetVertexAttribName());
        }
        if (vertShader->GetColorAttribName())
        {
            glBindAttribLocation(program->id, 1, vertShader->GetColorAttribName());
        }
        if (vertShader->GetNormalAttribName())
        {
            glBindAttribLocation(program->id, 2, vertShader->GetNormalAttribName());
        }

        glLinkProgram(program->id);

        system::INT32 result(0);
        glGetProgramiv(program->id, GL_LINK_STATUS, &result);
        program->linked = (result == GL_TRUE);

        if (program->linked)
        {
            char *vertexAttrib = (vertShader) ? vertShader->GetVertexAttribName() : 0;
            program->vertexAttribLoc = glGetAttribLocation(program->id, vertexAttrib);

            char *colorAttrib = (vertShader) ? vertShader->GetColorAttribName() : 0;
            program->colorAttribLoc = glGetAttribLocation(program->id, colorAttrib);

            char *normalAttrib = (vertShader) ? vertShader->GetNormalAttribName() : 0;
            program->normalAttribLoc = glGetAttribLocation(program->id, normalAttrib);
        }
    }

    return *program;
}
//------------------------------------------------------------------------------------------------------------------------
void GLRenderer::ImplementationUpdateViewport(system::INT32 x, system::INT32 y, system::UINT32 width, system::UINT32 height)
{
    glViewport(x, y, width, height);
}
//------------------------------------------------------------------------------------------------------------------------
GLRenderer::VertexShaderResourceData &GLRenderer::CompileShader(VertexShaderResource *resource)
{
    ResourceToVertexShaderDataMap::iterator it = _vertexShaderResourceDataMap.find(resource);
    if (it != _vertexShaderResourceDataMap.end())
    {
        if (!it->second.compiled)
        {
            const char *source = resource->GetSource();
            glShaderSource(it->second.id, 1, &source, 0);
            glCompileShader(it->second.id);

            system::INT32 result(0);
            glGetShaderiv(it->second.id, GL_COMPILE_STATUS, &result);
            it->second.compiled = (result == GL_TRUE);
        }

        return it->second;
    }

    VertexShaderResourceData vertData;
    vertData.id = glCreateShader(GL_VERTEX_SHADER);

    const char *source = resource->GetSource();
    glShaderSource(vertData.id, 1, &source, 0);
    glCompileShader(vertData.id);

    system::INT32 result(0);
    glGetShaderiv(vertData.id, GL_COMPILE_STATUS, &result);
    vertData.compiled = (result == GL_TRUE);

    char buffer[1024] = {0};
    GLsizei logLen = 0;
    glGetShaderInfoLog(vertData.id, 1024, &logLen, buffer);

    _vertexShaderResourceDataMap.insert(ResourceToVertexShaderDataPair(resource, vertData));

    return _vertexShaderResourceDataMap[resource];
}
//------------------------------------------------------------------------------------------------------------------------
GLRenderer::FragmentShaderResourceData &GLRenderer::CompileShader(FragmentShaderResource *resource)
{
    ResourceToFragmentShaderDataMap::iterator it = _fragmentShaderResourceDataMap.find(resource);
    if (it != _fragmentShaderResourceDataMap.end())
    {
        if (!it->second.compiled)
        {
            const char *source = resource->GetSource();
            glShaderSource(it->second.id, 1, &source, 0);
            glCompileShader(it->second.id);

            system::INT32 result(0);
            glGetShaderiv(it->second.id, GL_COMPILE_STATUS, &result);
            it->second.compiled = (result == GL_TRUE);
        }

        return it->second;
    }

    FragmentShaderResourceData fragData;
    fragData.id = glCreateShader(GL_FRAGMENT_SHADER);

    const char *source = resource->GetSource();
    glShaderSource(fragData.id, 1, &source, 0);
    glCompileShader(fragData.id);

    system::INT32 result(0);
    glGetShaderiv(fragData.id, GL_COMPILE_STATUS, &result);
    fragData.compiled = (result == GL_TRUE);

    char buffer[1024] = {0};
    GLsizei logLen = 0;
    glGetShaderInfoLog(fragData.id, 1024, &logLen, buffer);

    _fragmentShaderResourceDataMap.insert(ResourceToFragmentShaderDataPair(resource, fragData));

    return _fragmentShaderResourceDataMap[resource];
}
//------------------------------------------------------------------------------------------------------------------------
void GLRenderer::ApplyMaterial(Material &material, Camera *camera, Renderable *renderable)
{
    // TODO: Avoid setting opengl state redudnetly 
    glBindVertexArray(_glVertexArrays[0]);

    // TODO: Bind Texture

    VertexShaderResource *vertShader = (material.GetVertexShader()) ? material.GetVertexShader() : _defaultVertexShader;
    FragmentShaderResource *fragShader = (material.GetFragmentShader()) ? material.GetFragmentShader() : _defaultFragmentShader;

    if (vertShader || fragShader)
    {
        ShaderProgram &program = LinkShaderProgram(vertShader, fragShader);
        if (program.linked)
        {
            glUseProgram(program.id);

            // TODO: Not sure how i feel about this string check, staying for now..
            if (camera && material.GetProjectionMatrixShaderVar()[0] != 0)
            {
                program.projMatrixAttribLoc = glGetUniformLocation(program.id, material.GetProjectionMatrixShaderVar());
                if (program.projMatrixAttribLoc >= 0)
                {
                    const float *projMatrix = reinterpret_cast<const float *>(&(camera->GetProjectionMatrix()));
                    glUniformMatrix4fv(program.projMatrixAttribLoc, 1, GL_FALSE, projMatrix);
                }
            }

            if (camera && material.GetModelViewMatrixShaderVar()[0] != 0)
            {
                program.modelViewMatrixAttribLoc = glGetUniformLocation(program.id, material.GetModelViewMatrixShaderVar());
                if (program.modelViewMatrixAttribLoc >= 0)
                {
                    matrix4x4 modelViewMatrix = camera->GetViewMatrix();
                    if (renderable)
                    {
                        modelViewMatrix = modelViewMatrix * renderable->GetTransformMatrix();
                    }
                    const float *viewMatrix = reinterpret_cast<const float *>(&modelViewMatrix);
                    glUniformMatrix4fv(program.modelViewMatrixAttribLoc, 1, GL_FALSE, viewMatrix);
                }
            }

            if (program.colorAttribLoc > -1)
            {
                //glVertexAttrib3f(program.colorAttribLoc, 1.0f, 0.0f, 0.0f);
            }
        }
        else
        {
            glUseProgram(0);
        }
    }
    else
    {
        glUseProgram(0);
    }
}
//------------------------------------------------------------------------------------------------------------------------
void GLRenderer::RenderModel(ModelResourceData &data)
{
    glVertexPointer(3, GL_FLOAT, 0, (GLvoid *)data.vertexOffset);
    glIndexPointer(GL_UNSIGNED_INT, 0, (GLvoid *)data.indexOffset);

    glDrawElements(GL_TRIANGLES, data.indexCount, GL_UNSIGNED_INT, 0);
}
//------------------------------------------------------------------------------------------------------------------------
GLRenderer::ModelResourceData &GLRenderer::PushToGPU(ModelResource *resource)
{
    ResourceToModelDataMap::iterator it = _modelResourceDataMap.find(resource);
    if (it != _modelResourceDataMap.end())
    {
        return it->second;
    }

    const system::UINT32 vertexByteSize = resource->GetTotalVertices() * sizeof(vector3);
    const system::UINT32 indexByteSize = resource->GetTotalIndices() * sizeof(system::UINT32);

    ModelResourceData data;
    memset(&data, 0, sizeof(data));

    if (
        (vertexByteSize < (_staticVertexBuffer.totalSize - _staticVertexBuffer.usedSize)) &&
        (indexByteSize < (_staticIndexBuffer.totalSize - _staticIndexBuffer.usedSize))
        )
    {
        glBindBuffer(GL_ARRAY_BUFFER, _staticVertexBuffer.id);
        glBufferSubData(GL_ARRAY_BUFFER, _staticVertexBuffer.usedSize, vertexByteSize, resource->GetVertices());
        data.vertexCount = resource->GetTotalVertices();
        data.vertexOffset = _staticVertexBuffer.usedSize;

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _staticIndexBuffer.id);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, _staticIndexBuffer.usedSize, indexByteSize, resource->GetIndices());
        data.indexCount = resource->GetTotalIndices();
        data.indexOffset = _staticIndexBuffer.usedSize;

        _staticIndexBuffer.usedSize += indexByteSize;
        _staticVertexBuffer.usedSize += vertexByteSize;
    }
    else
    {
        // TODO: Log error
    }
    _modelResourceDataMap.insert(ResourceToModelDataPair(resource, data));

    return _modelResourceDataMap[resource];
}
} // renderer
} // engine
