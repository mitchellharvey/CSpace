// File:        resources/ResourceLoader.cpp
// Author:      Mitchell Harvey
// Date:        1/24/2012
// 

#include "resources/ResourceLoader.h"

#include "resources/ModelResource.h"
#include "resources/VertexShaderResource.h"
#include "resources/FragmentShaderResource.h"

#include "resources/TextureLoader.h"
#include "resources/ModelLoader.h"
#include "resources/ShaderLoader.h"

namespace engine {
namespace resources {

ResourceLoader::StringToResourceMap ResourceLoader::_sResourceMap;

Resource *ResourceLoader::GetResource(const system::utf8 &filename)
{
    StringToResourceMap::iterator iter = _sResourceMap.find(filename);
    if (iter != _sResourceMap.end())
    {
        return iter->second;
    }
    
    return 0;
}
//------------------------------------------------------------------------------------------------------------------------
void ResourceLoader::UnloadResource(Resource *resource)
{
    if (resource)
    {
        Resource::TYPE type = resource->GetType();
        switch (type)
        {
        case Resource::TEXTURE:
            break;

        case Resource::VERTEX_SHADER:
            UnloadVertexShader(reinterpret_cast<VertexShaderResource *>(resource));
            break;

        case Resource::MODEL:
            UnloadModel(reinterpret_cast<ModelResource *>(resource));
            break;
        };
    }
}
//------------------------------------------------------------------------------------------------------------------------
TextureResource *ResourceLoader::LoadTexture(const system::utf8 &filename, TextureLoader &loader)
{
    return 0;
}
//------------------------------------------------------------------------------------------------------------------------
FragmentShaderResource *ResourceLoader::LoadFragmentShader(const system::utf8 &filename, ShaderLoader &loader)
{
    FragmentShaderResource *resource = reinterpret_cast<FragmentShaderResource *>(ResourceLoader::GetResource(filename));
    if (!resource)
    {
        resource = new FragmentShaderResource(filename);

        if (loader.LoadShader(filename))
        {
            resource->_shaderSourceByteSize = loader.GetShaderSourceSize() + 1;
            resource->_shaderSource = new char[resource->_shaderSourceByteSize];
            memcpy(resource->_shaderSource, loader.GetShaderSource(), resource->_shaderSourceByteSize);

            loader.UnloadShader();
        }
    
        _sResourceMap.insert(StringToResourcePair(filename, resource));
    }

    return resource;
}
//------------------------------------------------------------------------------------------------------------------------
VertexShaderResource *ResourceLoader::LoadVertexShader(const system::utf8 &filename, ShaderLoader &loader)
{
    VertexShaderResource *resource = reinterpret_cast<VertexShaderResource *>(ResourceLoader::GetResource(filename));
    if (!resource)
    {
        resource = new VertexShaderResource(filename);

        if (loader.LoadShader(filename))
        {
            resource->_shaderSourceByteSize = loader.GetShaderSourceSize() + 1;
            resource->_shaderSource = new char[resource->_shaderSourceByteSize];
            memcpy(resource->_shaderSource, loader.GetShaderSource(), resource->_shaderSourceByteSize);

            resource->SetVertexAttribName("position");
            resource->SetNormalAttribName("normal");
            resource->SetColorAttribName("color");

            loader.UnloadShader();
        }
    
        _sResourceMap.insert(StringToResourcePair(filename, resource));
    }

    return resource;
}
//------------------------------------------------------------------------------------------------------------------------
ModelResource *ResourceLoader::LoadModel(const system::utf8 &filename, ModelLoader &loader)
{
    ModelResource *resource = reinterpret_cast<ModelResource *>(ResourceLoader::GetResource(filename));
    if (!resource)
    {
        resource = new ModelResource(filename);

        loader.LoadModel(filename);

        resource->_indexCount = loader.GetIndexCount();
        resource->_vertexCount = loader.GetVertexCount();
        resource->_normalCount = loader.GetNormalCount();
        resource->_uvCount = loader.GetUVCount();
        resource->_colorCount = loader.GetColorCount();

        resource->_indices = (resource->_indexCount) ? new system::UINT32[resource->_indexCount] : 0;
        resource->_vertices = (resource->_vertexCount) ? new math::vector3[resource->_vertexCount] : 0;
        resource->_normals = (resource->_normalCount) ? new math::vector3[resource->_normalCount] : 0;
        resource->_uvs = (resource->_uvCount) ? new math::vector2[resource->_uvCount] : 0;
        resource->_colors = (resource->_colorCount) ? new math::vector4[resource->_colorCount] : 0;

        memcpy(resource->_indices, loader.GetIndices( ), sizeof(system::UINT32) * resource->_indexCount); 
        memcpy(resource->_vertices, loader.GetVertices( ), sizeof(math::vector3) * resource->_vertexCount);
        memcpy(resource->_normals, loader.GetNormals( ), sizeof(math::vector3) * resource->_normalCount);
        memcpy(resource->_uvs, loader.GetUVs(), sizeof(math::vector2) * resource->_uvCount);
        memcpy(resource->_colors, loader.GetColors(), sizeof(math::vector4) * resource->_colorCount);

        loader.UnloadModel();
    
        _sResourceMap.insert(StringToResourcePair(filename, resource));
    }

    return resource;
}
//------------------------------------------------------------------------------------------------------------------------
void ResourceLoader::UnloadVertexShader(VertexShaderResource *resource)
{
    delete [] resource->_shaderSource;

    resource->_shaderSource = 0;
    resource->_shaderSourceByteSize = 0;
}
//------------------------------------------------------------------------------------------------------------------------
void ResourceLoader::UnloadFragmentShader(FragmentShaderResource *resource)
{
    delete [] resource->_shaderSource;

    resource->_shaderSource = 0;
    resource->_shaderSourceByteSize = 0;
}
//------------------------------------------------------------------------------------------------------------------------
void ResourceLoader::UnloadModel(ModelResource *resource)
{
    delete [] resource->_vertices;
    delete [] resource->_indices;
    delete [] resource->_uvs;
    delete [] resource->_normals;

    resource->_vertices = 0;
    resource->_indices = 0;
    resource->_uvs = 0;
    resource->_normals = 0;

    resource->_vertexCount = 0;
    resource->_normalCount = 0;
    resource->_indexCount  = 0;
    resource->_uvCount = 0;
}
} // resources
} // engine
