#pragma once

#include "fpoint.hpp"
#include "color.hpp"

namespace tr {

struct point;

struct vertex : public fpoint {
    using fpoint::fpoint;
    operator point() const;
    color c = {-1, -1, -1};
    vertex(fpoint p, color c);
};

}