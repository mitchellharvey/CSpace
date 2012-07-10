// File:        resources/PrimitiveLoader.cpp
// Author:      Mitchell Harvey
// Date:        2/2/2012
// 

#include "resources/PrimitiveLoader.h"

using namespace engine::math;

namespace engine {
namespace resources {

PrimitiveLoader::PrimitiveLoader(const PRIMITIVE type) :
_type(type)
{
}
//------------------------------------------------------------------------------------------------------------------------
PrimitiveLoader::~PrimitiveLoader()
{
    UnloadModel();
}
//------------------------------------------------------------------------------------------------------------------------
bool PrimitiveLoader::LoadModel(const system::utf8 &filename)
{
    bool loaded = false;

    UnloadModel();

    // These are hardcoded to be CCW winding order
    switch(_type)
    {
        case TRIANGLE:
        {
           system::UINT32   indices[]   = { 0, 1, 2 };
           vector3  vertices[]  = { 
                                    vector3(0.0f, 0.5f, 0.0f),      // TOP
                                    vector3(-0.5f, -0.5f, 0.0f),    // BOTTOM LEFT
                                    vector3(0.5f, -0.5f, 0.0f)      // BOTTOM RIGHT
                                  };

           vector3  normals[]   = {
                                    vector3(0.0f, 0.0f, 1.0f),
                                    vector3(0.0f, 0.0f, 1.0f),
                                    vector3(0.0f, 0.0f, 1.0f)
                                  };

           vector4 colors[]    = {
                                    vector4(1.0f, 0.0f, 0.0f, 0.0f),
                                    vector4(0.0f, 1.0f, 0.0f, 1.0f),
                                    vector4(0.0f, 0.0f, 1.0f, 1.0f)
                                 };

           CopyData(vertices, 
                    normals, 
                    indices, 
                    0,
                    colors,
                    sizeof(vertices) / sizeof(vector3),
                    sizeof(normals) / sizeof(vector3),
                    sizeof(indices) / sizeof(system::UINT32),
                    0,
                    sizeof(colors) / sizeof(vector4));
        }
        break;
    }

    return loaded;
}
//------------------------------------------------------------------------------------------------------------------------
void PrimitiveLoader::UnloadModel()
{
    delete [] _vertices;
    delete [] _indices;
    delete [] _uvs;
    delete [] _normals;
    delete [] _colors;
    _vertexCount = _indexCount = _uvCount = _normalCount = _colorCount = 0;
    _vertices = 0;
    _indices = 0;
    _uvs = 0;
    _normals = 0;
    _colors = 0;
}
//------------------------------------------------------------------------------------------------------------------------
void PrimitiveLoader::CopyData(const vector3 *vertices, const vector3 *normals, const system::UINT32 *indices, const vector2 *uvs,
                               const vector4 *colors, system::UINT32 vertexCount, system::UINT32 normalCount, system::UINT32 indexCount, system::UINT32 uvCount, system::UINT32 colorCount)
{
    if (vertices && vertexCount)
    {
        _vertexCount = vertexCount;
        _vertices = new vector3[_vertexCount];
        memcpy(_vertices, vertices, _vertexCount * sizeof(vector3));
    }

    if (normals && normalCount)
    {
        _normalCount = normalCount;
        _normals = new vector3[_normalCount];
        memcpy(_normals, normals, _normalCount * sizeof(vector3));
    }

    if (indices && indexCount)
    {
        _indexCount = indexCount;
        _indices = new system::UINT32[_indexCount];
        memcpy(_indices, indices, _indexCount * sizeof(system::UINT32));
    }

    if (uvs && uvCount)
    {
        _uvCount = uvCount;
        _uvs = new vector2[_uvCount];
        memcpy(_uvs, uvs, _uvCount * sizeof(vector2));
    }

    if (colors && colorCount)
    {
        _colorCount = colorCount;
        _colors = new vector4[_colorCount];
        memcpy(_colors, colors, _colorCount * sizeof(vector4));
    }
}
} // resources
} // engine
