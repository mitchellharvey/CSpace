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
           CreateTriangle();
        }
        break;

        case CUBE:
        {
            CreateCube();
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
void PrimitiveLoader::CreateTriangle(void)
{
    system::UINT32  indices[]   = { 0, 1, 2 };
    vector3         vertices[]  = { 
                                    vector3(0.0f, 0.5f, 0.0f),      // TOP
                                    vector3(-0.5f, -0.5f, 0.0f),    // BOTTOM LEFT
                                    vector3(0.5f, -0.5f, 0.0f)      // BOTTOM RIGHT
                                  };

    vector2         uvs[]       = {
                                    vector2(0.5f, 1.0f),
                                    vector2(0.0f, 0.0f),
                                    vector2(1.0f, 0.0f)
                                  };

    vector3         normals[]   = {
                                    vector3(0.0f, 0.0f, 1.0f),
                                    vector3(0.0f, 0.0f, 1.0f),
                                    vector3(0.0f, 0.0f, 1.0f)
                                  };

    vector4         colors[]    = {
                                    vector4(1.0f, 0.0f, 0.0f, 0.0f),
                                    vector4(0.0f, 1.0f, 0.0f, 1.0f),
                                    vector4(0.0f, 0.0f, 1.0f, 1.0f)
                                  };

    _vertexCount = sizeof(vertices) / sizeof(vector3);
    _vertices = new vector3[_vertexCount];
    memcpy(_vertices, vertices, _vertexCount * sizeof(vector3));

    _normalCount = sizeof(normals) / sizeof(vector3);
    _normals = new vector3[_normalCount];
    memcpy(_normals, normals, _normalCount * sizeof(vector3));

    _indexCount = sizeof(indices) / sizeof(system::UINT32);
    _indices = new system::UINT32[_indexCount];
    memcpy(_indices, indices, _indexCount * sizeof(system::UINT32));

    _uvCount = sizeof(uvs) / sizeof(vector2);
    _uvs = new vector2[_uvCount];
    memcpy(_uvs, uvs, _uvCount * sizeof(vector2));

    _colorCount = sizeof(colors) / sizeof(vector4);
    _colors = new vector4[_colorCount];
    memcpy(_colors, colors, _colorCount * sizeof(vector4));
}
//------------------------------------------------------------------------------------------------------------------------
void PrimitiveLoader::CreateCube(void)
{
    const float LEFT = -0.5f;
    const float RIGHT = 0.5f;
    const float UP = 0.5f;
    const float DOWN = -0.5f;
    const float FRONT = 0.5f;
    const float BACK = -0.5f;

    system::UINT32  indices[]   = { 
                                    // FRONT
                                    0, 1, 2, 3, 0, 2,
                                    // BACK
                                    7, 6, 5, 5, 4, 7,
                                    // LEFT
                                    4, 5, 1, 1, 0, 4,
                                    // RIGHT
                                    3, 2, 6, 6, 7, 3,
                                    // TOP
                                    4, 0, 3, 3, 7, 4,
                                    // BOTTOM
                                    6, 2, 1, 1, 5, 6
                                  };

    vector3         vertices[]  = { 
                                    vector3(LEFT, UP, FRONT),       // 0
                                    vector3(LEFT, DOWN, FRONT),     // 1
                                    vector3(RIGHT, DOWN, FRONT),    // 2
                                    vector3(RIGHT, UP, FRONT),      // 3

                                    vector3(LEFT, UP, BACK),        // 4
                                    vector3(LEFT, DOWN, BACK),      // 5
                                    vector3(RIGHT, DOWN, BACK),     // 6
                                    vector3(RIGHT, UP, BACK)        // 7
                                  };

    vector2         uvs[]       = {
                                    vector2(LEFT, UP),
                                    vector2(LEFT, DOWN),
                                    vector2(RIGHT, DOWN),
                                    vector2(RIGHT, UP),

                                    vector2(LEFT, UP),
                                    vector2(LEFT, DOWN),
                                    vector2(RIGHT, DOWN),
                                    vector2(RIGHT, UP)
                                  };

    vector3         normals[]   = {
                                    vector3(0.0f, 0.0f, 1.0f),
                                    vector3(0.0f, 0.0f, 1.0f),
                                    vector3(0.0f, 0.0f, 1.0f),
                                    vector3(0.0f, 0.0f, 1.0f),

                                    vector3(0.0f, 0.0f, 1.0f),
                                    vector3(0.0f, 0.0f, 1.0f),
                                    vector3(0.0f, 0.0f, 1.0f),
                                    vector3(0.0f, 0.0f, 1.0f)
                                  };

    vector4         colors[]    = {
                                    vector4(1.0f, 0.0f, 0.0f, 0.0f),
                                    vector4(0.0f, 1.0f, 0.0f, 1.0f),
                                    vector4(0.0f, 0.0f, 1.0f, 1.0f),
                                    vector4(1.0f, 1.0f, 1.0f, 1.0f),

                                    vector4(1.0f, 0.0f, 0.0f, 0.0f),
                                    vector4(0.0f, 1.0f, 0.0f, 1.0f),
                                    vector4(0.0f, 0.0f, 1.0f, 1.0f),
                                    vector4(1.0f, 1.0f, 1.0f, 1.0f),
                                  };

    _vertexCount = sizeof(vertices) / sizeof(vector3);
    _vertices = new vector3[_vertexCount];
    memcpy(_vertices, vertices, _vertexCount * sizeof(vector3));

    _normalCount = sizeof(normals) / sizeof(vector3);
    _normals = new vector3[_normalCount];
    memcpy(_normals, normals, _normalCount * sizeof(vector3));

    _indexCount = sizeof(indices) / sizeof(system::UINT32);
    _indices = new system::UINT32[_indexCount];
    memcpy(_indices, indices, _indexCount * sizeof(system::UINT32));

    _uvCount = sizeof(uvs) / sizeof(vector2);
    _uvs = new vector2[_uvCount];
    memcpy(_uvs, uvs, _uvCount * sizeof(vector2));

    _colorCount = sizeof(colors) / sizeof(vector4);
    _colors = new vector4[_colorCount];
    memcpy(_colors, colors, _colorCount * sizeof(vector4));
}
} // resources
} // engine
