#pragma once

#include <vector>
#include <string>

#include "point.hpp"
#include "color.hpp"

namespace tr {

class Screen {
protected:
    std::vector<std::string> data;
	int width = 1, height = 1;
public:
	Screen();
	Screen(int w, int h);
    void clear();
    void putPixel(const point& p, const std::string& s);
	void putPixel(const point& p, const color& c);
    void print();
    void doublePrint();
};

}