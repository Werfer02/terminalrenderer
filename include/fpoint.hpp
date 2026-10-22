#pragma once

#include "numPair.hpp"

namespace tr {

struct point;
struct vec2D;

struct fpoint : public numPair<float> {
    using numPair<float>::numPair;
    fpoint(const numPair<float>& p) : numPair<float>(p) {}
    fpoint(const numPair<int>& p) : numPair<float>(p.x, p.y) {}

    operator point() const;
    operator vec2D() const;
};

}