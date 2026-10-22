#pragma once

#include "fpoint.hpp"

namespace tr {

struct point;

struct vec2D : public fpoint {
    using fpoint::fpoint;
    operator point() const;

    static float cross(const vec2D& v1, const vec2D& v2);
    static vec2D toLocal(const vec2D& p, const vec2D& origin, const vec2D& up, const vec2D& right);
    float mag() const;
};

}