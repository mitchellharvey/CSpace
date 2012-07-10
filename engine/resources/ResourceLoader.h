// File:        resources/ResourceLoader.h
// Author:      Mitchell Harvey
// Date:        1/24/2012
// 

#ifndef ENGINE_RESOURCES_RESOURCELOADER_H_
#define ENGINE_RESOURCES_RESOURCELOADER_H_

#include <unordered_map>

#include "system/types.h"
#include "system/utf8.h"

namespace engine {
namespace resources {

class Resource;
class ModelResource;
class VertexShaderResource;
class FragmentShaderResource;
class TextureResource;

class TextureLoader;
class ModelLoader;
class ShaderLoader;

class ResourceLoader
{
public:
    static TextureResource *LoadTexture(const system::utf8 &filename, TextureLoader &loader);
    static ModelResource *LoadModel(const system::utf8 &filename, ModelLoader &loader);
    static VertexShaderResource *LoadVertexShader(const system::utf8 &filename, ShaderLoader &loader);
    static FragmentShaderResource *LoadFragmentShader(const system::utf8 &filename, ShaderLoader &loader);

    static Resource *GetResource(const system::utf8 &filename);

    static void UnloadResource(Resource *resource);

protected:
    ResourceLoader() {}
    ResourceLoader(const ResourceLoader &) {}
    ~ResourceLoader() {}

    static void UnloadModel(ModelResource *resource);
    static void UnloadVertexShader(VertexShaderResource *resource);
    static void UnloadFragmentShader(FragmentShaderResource *resource);

    typedef std::unordered_map<const system::utf8, Resource *, std::hash<system::utf8>> StringToResourceMap;
    typedef std::pair<const system::utf8, Resource *> StringToResourcePair;
    static StringToResourceMap _sResourceMap;

};
} // resources
} // engine
#endif // ENGINE_RESOURCES_RESOURCELOADER_H_
