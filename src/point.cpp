#include "point.hpp"

#include "fpoint.hpp"
#include "vec2D.hpp"

namespace tr {

point::operator fpoint() const {
    return {(float)x, (float)y};
}
point::operator vec2D() const {
    return {(float)x, (float)y};
}

}