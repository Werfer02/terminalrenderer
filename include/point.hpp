#pragma once

#include "numPair.hpp"

namespace tr {

struct fpoint;
struct vec2D;

struct point : public numPair<int> {
    using numPair<int>::numPair;
    point(const numPair<int>& p) : numPair<int>(p) {}
    point(const numPair<float>& p) : numPair<int>(p.x, p.y) {}

    operator fpoint() const;
    operator vec2D() const;
};

}