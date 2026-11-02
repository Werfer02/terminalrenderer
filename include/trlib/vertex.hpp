#pragma once

#include "fpoint.hpp"
#include "color.hpp"
#include "vec2D.hpp"

namespace tr {

struct point;

struct vertex : public fpoint {
    using fpoint::fpoint;
    operator point() const;
    color c = {0, 0, 0};
    vec2D uv = {0, 0};
    vertex(fpoint p, color c);
    vertex(fpoint p, color c, vec2D uv);
};

}