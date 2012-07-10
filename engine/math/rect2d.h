// File:        math/rect2d.h
// Author:      Mitchell Harvey
// Date:        3/31/2011
// 

#ifndef ENGINE_MATH_RECT2D_H_
#define ENGINE_MATH_RECT2D_H_

#include "math/vector.h"

namespace engine {
namespace math {

struct rect2d
{
    rect2d(float width, float height, float x, float y);
    rect2d(float width, float height, const vector2 &v);
    rect2d(const rect2d &r);
    rect2d(void);

    rect2d &set(float width, float height, float x, float y);
    rect2d &set(float width, float height, const vector2 &v);

    rect2d &set_size(float width, float height);

    rect2d &set_position(float x, float y);
    rect2d &set_position(const vector2 &v);

    vector2 center(void) const;

    rect2d &operator=(const rect2d &r);

    bool operator==(const rect2d &v) const;
    bool operator!=(const rect2d &v) const;

    float _width, _height;
    vector2 _position;
};

} // math
} // engine
#endif // ENGINE_MATH_RECT2D_H_
