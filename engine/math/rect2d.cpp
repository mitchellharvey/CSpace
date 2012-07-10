// File:        math/rect2d.cpp
// Author:      Mitchell Harvey
// Date:        3/31/2011
// 

#include "math/rect2d.h"

namespace engine {
namespace math {

rect2d::rect2d(float width, float height, const vector2 &v) : _width(width), _height(height), _position(v)
{
}
//------------------------------------------------------------------------------------------------------------------------
rect2d::rect2d(float width, float height, float x, float y) : _width(width), _height(height), _position(x, y)
{
}
//------------------------------------------------------------------------------------------------------------------------
rect2d::rect2d(const rect2d &r) : _width(r._width), _height(r._height), _position(r._position)
{
}
//------------------------------------------------------------------------------------------------------------------------
rect2d::rect2d(void) : _width(0.0f), _height(0.0f), _position(0.0f, 0.0f)
{
}
//------------------------------------------------------------------------------------------------------------------------
rect2d &rect2d::set(float width, float height, float x, float y)
{
    _width = width; _height = height;
    _position.set(x, y);
    return *this;
}
//------------------------------------------------------------------------------------------------------------------------
rect2d &rect2d::set(float width, float height, const vector2 &v)
{
    _width = width; _height = height;
    _position = v;
    return *this;
}
//------------------------------------------------------------------------------------------------------------------------
rect2d &rect2d::set_size(float width, float height)
{
    _width = width; _height = height;
    return *this;
}
//------------------------------------------------------------------------------------------------------------------------
rect2d &rect2d::set_position(float x, float y)
{
    _position.set(x, y);
    return *this;
}
//------------------------------------------------------------------------------------------------------------------------
rect2d &rect2d::set_position(const vector2 &v)
{
    _position = v;
    return *this;
}
//------------------------------------------------------------------------------------------------------------------------
vector2 rect2d::center(void) const
{
    vector2 center = _position;
    center.x += _width * 0.5f;
    center.y += _height * 0.5f;
    return center;
}
//------------------------------------------------------------------------------------------------------------------------
rect2d &rect2d::operator=(const rect2d &r)
{
    _width = r._width; _height = r._height;
    _position = r._position;
    return *this;
}
//------------------------------------------------------------------------------------------------------------------------
bool rect2d::operator==(const rect2d &r) const
{
    return (_width == r._width && _height == r._height && _position == r._position);
}
//------------------------------------------------------------------------------------------------------------------------
bool rect2d::operator!=(const rect2d &r) const
{
    return !(*this == r);
}
} // math
} // engine
