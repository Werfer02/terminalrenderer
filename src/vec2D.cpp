#include "vec2D.hpp"

#include <cmath>

#include "point.hpp"

namespace tr {

vec2D::operator point() const {
    return {(int)x, (int)y};
}

float vec2D::cross(const vec2D& v1, const vec2D& v2){
    return {v1.x * v2.y - v2.x * v1.y};
}

vec2D vec2D::toLocal(const vec2D& p, const vec2D& origin, const vec2D& up, const vec2D& right){
    vec2D rel = p - origin;

    float det = cross(up, right);

    return {cross(rel, right) / det, cross(up, rel) / det};
}

float vec2D::mag() const {
    return std::sqrt(x*x + y*y);
}

}