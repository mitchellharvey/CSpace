// File:        math/vector.h
// Author:      Mitchell Harvey
// Date:        3/21/2011
//
// TODO:        Study up on SSE instructions and caching to convert this into a vectorized library of SIMD instructions
//

#include "math/util.h"

#ifndef ENGINE_MATH_VECTOR_H_
#define ENGINE_MATH_VECTOR_H_

namespace engine {
namespace math {
    
struct vector2
{
    float x, y;

    inline vector2(float x, float y) :x(x), y(y) { }
    inline vector2(const vector2 &v) : x(v.x), y(v.y) { }
    inline vector2(void) : x(0.0f), y(0.0f) { }
    inline vector2 &set(float x, float y)
    {
        this->x = x; this->y = y;
        return *this;
    }   
    inline vector2 &operator=(const vector2 &v)
    {
        x = v.x; y = v.y;
        return *this;
    }
    inline bool operator==(const vector2 &v) const
    {
        return (x == v.x && y == v.y);
    }
    inline bool operator!=(const vector2 &v) const
    {
        return !(*this == v);
    }
    inline const vector2 operator*(const float scale) const
    {
        return vector2(x * scale, y * scale);
    }
    inline vector2 &operator*=(const float scale)
    {
        x *= scale; y *= scale;
        return *this;
    }
    inline const vector2 operator+(const vector2 &v) const
    {
        return vector2(x + v.x, y + v.y);
    }
    inline vector2 &operator+=(const vector2 &v)
    {
        x += v.x; y += v.y;
        return *this;
    }
    inline const vector2 operator-(const vector2 &v) const
    {
        return vector2(x - v.x, y - v.y);
    }
    inline vector2 &operator-=(const vector2 &v)
    {
        x -= v.x; y -= v.y;
        return *this;
    }
};

static inline const vector2 operator*(float scale, const vector2 &v)
{
    return v * scale;
}

struct vector3
{
    float x, y, z;

    inline vector3(float x, float y, float z) : x(x), y(y), z(z) { }
    inline vector3(const vector3 &v) : x(v.x), y(v.y), z(v.z) { }
    inline vector3(void) : x(0.0f), y(0.0f), z(0.0f) { }
    inline vector3 &set(float x, float y, float z) 
    { 
        this->x = x; this->y = y; this->z = z;
    }
    inline vector3 &operator=(const vector3 &v)
    {
        x = v.x; y = v.y; z = v.z;
        return *this;
    }
    inline bool operator==(const vector3 &v) const
    {
        return (x == v.x && y == v.y && z == v.z);
    }
    inline bool operator!=(const vector3 &v) const
    {
        return !(*this == v);
    }
    inline const vector3 operator*(const float scale) const
    {
        return vector3(x * scale, y * scale, z * scale);
    }
    inline vector3 &operator*=(const float scale)
    {
        x *= scale; y *= scale; z *= scale;
        return *this;
    }
    inline const vector3 operator+(const vector3 &v) const
    {
        return vector3(x + v.x, y + v.y, z + v.z);
    }
    inline vector3 &operator+=(const vector3 &v)
    {
        x += v.x; y += v.y; z += v.z;
        return *this;
    }
    inline const vector3 operator-(const vector3 &v) const
    {
        return vector3(x - v.x, y - v.y, z - v.z);
    }
    inline vector3 &operator-=(const vector3 &v)
    {
        x -= v.x; y -= v.y; z -= v.z;
        return *this;
    }
};

static inline const vector3 operator*(float scale, const vector3 &v)
{
    return v * scale;
}

static inline vector3 v3CrossProduct(const vector3 &v1, const vector3 &v2)
{
    vector3 r;
    r.x = v1.y * v2.z - v2.y * v1.z;
    r.y = v1.z * v2.x - v2.z * v1.x;
    r.z = v1.x * v2.y - v2.x * v1.y;
    return r;
}

static inline float v3MagnitudeSquared(const vector3 &v)
{
    return v.x * v.x + v.y * v.y + v.z * v.z;
}

static inline float v3Magnitude(const vector3 &v)
{
    return sqrt(v3MagnitudeSquared(v));
}

static inline void v3Normalize(vector3 &v)
{
    float len = v3Magnitude(v);

    if (len == 0)
        len = 1;

    v = v * (1.0f / len);
}

} // math
} // engine
#endif // ENGINE_MATH_VECTOR_H_
