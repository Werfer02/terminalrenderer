#include "fpoint.hpp"

#include "point.hpp"
#include "vec2D.hpp"

namespace tr {

fpoint::operator point() const {
    return {(int)x, (int)y};
}
fpoint::operator vec2D() const {
    return {x, y};
}

}