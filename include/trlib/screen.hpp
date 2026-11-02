#pragma once

#include <vector>
#include <string>

#include "point.hpp"
#include "color.hpp"

namespace tr {

class Screen {
protected:
    std::u32string characters;
    std::vector<color> colors;
	int width = 1, height = 1;
public:
	Screen();
	Screen(int w, int h);
    void clear();
    void clear(const color& c);
    void putChar(const point& p, char32_t s);
    void putColor(const point& p, const color& s);
	void putPixel(const point& p, const color& c);
    void print();
    void doublePrint();
};

}