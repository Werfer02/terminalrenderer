#include "vertex.hpp"

#include "point.hpp"

namespace tr {

vertex::operator point() const {
    return {(int)x, (int)y};
}

vertex::vertex(fpoint p, color inc) : fpoint(p) , c(inc) {}
vertex::vertex(fpoint p, color inc, vec2D inuv) : fpoint(p) , c(inc), uv(inuv) {}

}