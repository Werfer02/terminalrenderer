#pragma once

namespace tr {

template <typename T>
struct numPair{
    T x = 0, y = 0;
    numPair(T inx, T iny) : x(inx), y(iny) {}
    numPair operator+(const numPair& p) const {
        return {x + p.x, y + p.y};
    }
    numPair operator-(const numPair& p) const {
        return {x - p.x, y - p.y};
    }
    numPair operator*(const numPair& p) const {
        return {x * p.x, y * p.y};
    }
    numPair operator/(const numPair& p) const {
        return {x / p.x, y / p.y};
    }
    numPair& operator+=(const numPair& p){
        x += p.x, y += p.y;
        return *this;
    }
    numPair& operator-=(const numPair& p){
        x -= p.x, y -= p.y;
        return *this;
    }
    numPair& operator*=(const numPair& p){
        x *= p.x, y *= p.y;
        return *this;
    }
    numPair& operator/=(const numPair& p){
        x /= p.x, y /= p.y;
        return *this;
    };

    numPair operator*(float s) const {
        return {x * s, y * s};
    }
    numPair operator/(float s) const {
        return {x / s, y / s};
    }
    numPair& operator*=(float s) {
        x *= s;
        y *= s;
        return *this;
    }
    numPair& operator/=(float s) {
        x /= s;
        y /= s;
        return *this;
    }
};

}