#include "vertex.hpp"

#include "point.hpp"

namespace tr {

vertex::operator point() const {
    return {(int)x, (int)y};
}

vertex::vertex(fpoint p, color inc) : fpoint(p) , c(inc) {}

}