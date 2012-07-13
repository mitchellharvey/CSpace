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

struct vector4
{
    float x, y, z, w;

    inline vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) { }
    inline vector4(const vector4 &v) : x(v.x), y(v.y), z(v.z), w(v.w) { }
    inline vector4(void) : x(0.0f), y(0.0f), z(0.0f), w(0.0f) { }
    inline vector4 &set(float x, float y, float z, float w) 
    { 
        this->x = x; this->y = y; this->z = z;
        this->w = w;
    }
    inline vector4 &operator=(const vector4 &v)
    {
        x = v.x; y = v.y; z = v.z; w = v.w;
        return *this;
    }
    inline bool operator==(const vector4 &v) const
    {
        return (x == v.x && y == v.y && z == v.z && w == v.w);
    }
    inline bool operator!=(const vector4 &v) const
    {
        return !(*this == v);
    }
    inline const vector4 operator*(const float scale) const
    {
        return vector4(x * scale, y * scale, z * scale, w * scale);
    }
    inline vector4 &operator*=(const float scale)
    {
        x *= scale; y *= scale; z *= scale; w *= scale;
        return *this;
    }
    inline const vector4 operator+(const vector4 &v) const
    {
        return vector4(x + v.x, y + v.y, z + v.z, w + v.w);
    }
    inline vector4 &operator+=(const vector4 &v)
    {
        x += v.x; y += v.y; z += v.z; w += v.w;
        return *this;
    }
    inline const vector4 operator-(const vector4 &v) const
    {
        return vector4(x - v.x, y - v.y, z - v.z, w - v.w);
    }
    inline vector4 &operator-=(const vector4 &v)
    {
        x -= v.x; y -= v.y; z -= v.z; w -= v.w;
        return *this;
    }
};

static inline const vector4 operator*(float scale, const vector4 &v)
{
    return v * scale;
}

static inline vector3 CrossProduct(const vector3 &v1, const vector3 &v2)
{
    vector3 r;
    r.x = v1.y * v2.z - v2.y * v1.z;
    r.y = v1.z * v2.x - v2.z * v1.x;
    r.z = v1.x * v2.y - v2.x * v1.y;
    return r;
}

static inline float MagnitudeSquared(const vector3 &v)
{
    return v.x * v.x + v.y * v.y + v.z * v.z;
}

static inline float MagnitudeSquared(const vector2 &v)
{
    return v.x * v.x + v.y * v.y;
}

static inline float Magnitude(const vector3 &v)
{
    return sqrt(MagnitudeSquared(v));
}

static inline float Magnitude(const vector2 &v)
{
    return sqrt(MagnitudeSquared(v));
}

static inline vector3 &Normalize(vector3 &v)
{
    float len = Magnitude(v);

    if (len == 0)
        len = 1;

    v = v * (1.0f / len);

    return v;
}

static inline vector2 &Normalize(vector2 &v)
{
    float len = Magnitude(v);

    if (len == 0)
        len = 1;

    v = v * (1.0f / len);

    return v;
}

} // math
} // engine
#endif // ENGINE_MATH_VECTOR_H_
