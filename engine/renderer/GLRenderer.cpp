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

    // http://www.opengl.org/wiki/Tutorial:_OpenGL_3.1_The_First_Triangle_(C%2B%2B/Win)

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

    _staticVertexBuffer.usedSize = 0;
    _staticVertexBuffer.totalSize = cStaticVertexBufferSize;

    // Index Buffer
    glGenBuffers(1, &_staticIndexBuffer.id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _staticIndexBuffer.id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, cStaticIndexBufferSize, NULL, GL_STATIC_DRAW);

    _staticIndexBuffer.usedSize = 0;
    _staticIndexBuffer.totalSize = cStaticIndexBufferSize;

    // Color Buffer
    glGenBuffers(1, &_staticColorBuffer.id);
    glBindBuffer(GL_ARRAY_BUFFER, _staticColorBuffer.id);
    glBufferData(GL_ARRAY_BUFFER, cStaticVertexBufferSize, NULL, GL_STATIC_DRAW);

    _staticColorBuffer.usedSize = 0;
    _staticColorBuffer.totalSize = cStaticVertexBufferSize;

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
        pScene->GetSortedRenderables(renderables);
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
            // TODO: Each vertex array represents a unique way of buffering data into variables for the shader.
            // for now, we only support passing in this data but later? :)
            glBindVertexArray(_glVertexArrays[0]);

            // Position
            char *vertexAttrib = (vertShader) ? vertShader->GetVertexAttribName() : 0;
            program->vertexAttribLoc = glGetAttribLocation(program->id, vertexAttrib);
            glBindBuffer(GL_ARRAY_BUFFER, _staticVertexBuffer.id);
            glVertexAttribPointer(program->vertexAttribLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
            glEnableVertexAttribArray(program->vertexAttribLoc);

            // Color
            char *colorAttrib = (vertShader) ? vertShader->GetColorAttribName() : 0;
            program->colorAttribLoc = glGetAttribLocation(program->id, colorAttrib);
            glBindBuffer(GL_ARRAY_BUFFER, _staticColorBuffer.id);
            glVertexAttribPointer(program->colorAttribLoc, 4, GL_FLOAT, GL_FALSE, 0, 0);
            glEnableVertexAttribArray(program->colorAttribLoc);

            // Normals
            char *normalAttrib = (vertShader) ? vertShader->GetNormalAttribName() : 0;
            program->normalAttribLoc = glGetAttribLocation(program->id, normalAttrib);

            glBindVertexArray(0);
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
                // TODO: To avoid the constant updating of uniforms on each apply material, we should cache the values inside
                // the program so we don't set it if not neccesary, at least..  Consider refacoring these couple functions later
                // I don't like having to send in the camera to ApplyMaterial()
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
                        modelViewMatrix = renderable->GetTransformMatrix() * modelViewMatrix;
                    }
                    const float *viewMatrix = reinterpret_cast<const float *>(&modelViewMatrix);
                    glUniformMatrix4fv(program.modelViewMatrixAttribLoc, 1, GL_FALSE, viewMatrix);
                }
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
    glBindVertexArray(_glVertexArrays[0]);
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
    const system::UINT32 colorByteSize = resource->GetTotalColors() * sizeof(vector4);

    ModelResourceData data;
    memset(&data, 0, sizeof(data));

    if (
        (vertexByteSize < (_staticVertexBuffer.totalSize - _staticVertexBuffer.usedSize)) &&
        (indexByteSize < (_staticIndexBuffer.totalSize - _staticIndexBuffer.usedSize)) &&
        (colorByteSize < (_staticColorBuffer.totalSize - _staticColorBuffer.usedSize))
        )
    {
        glBindBuffer(GL_ARRAY_BUFFER, _staticVertexBuffer.id);
        glBufferSubData(GL_ARRAY_BUFFER, _staticVertexBuffer.usedSize, vertexByteSize, resource->GetVertices());
        data.vertexCount = resource->GetTotalVertices();
        data.vertexOffset = _staticVertexBuffer.usedSize;

        glBindBuffer(GL_ARRAY_BUFFER, _staticColorBuffer.id);
        glBufferSubData(GL_ARRAY_BUFFER, _staticColorBuffer.usedSize, colorByteSize, resource->GetColors());
        data.colorCount = resource->GetTotalColors();
        data.colorOffset = _staticColorBuffer.usedSize;

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _staticIndexBuffer.id);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, _staticIndexBuffer.usedSize, indexByteSize, resource->GetIndices());
        data.indexCount = resource->GetTotalIndices();
        data.indexOffset = _staticIndexBuffer.usedSize;

        _staticIndexBuffer.usedSize += indexByteSize;
        _staticVertexBuffer.usedSize += vertexByteSize;
        _staticColorBuffer.usedSize += colorByteSize;
    }
    else
    {
        // TODO: Attempt to defragment memeory?... hehe we aren't handling this anytime soon, kick up the constants.
    }
    _modelResourceDataMap.insert(ResourceToModelDataPair(resource, data));

    return _modelResourceDataMap[resource];
}
} // renderer
} // engine
