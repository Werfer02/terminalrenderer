#pragma once

#include "screen.hpp"
#include "vertex.hpp"

namespace tr {

class RenderScreen : public Screen {
    color drawColor = {255, 255, 255};
public:
    RenderScreen() : Screen() {}
    RenderScreen(int w, int h) : Screen(w, h) {}

    void drawLine(vertex start, vertex end);
    void drawLine(point start, point end);
    void drawLines(const std::vector<vertex>& vertices);
    void drawLines(const std::vector<point>& points);

    void drawTri(const vertex& p1, const vertex& p2, const vertex& p3);
    void drawTri(const point& p1, const point& p2, const point& p3);
    void drawTris(const std::vector<vertex>& vertices);
    void drawTris(const std::vector<point>& points);
    void drawTrisIndexed(const std::vector<vertex>& vertices, const std::vector<int>& indices);
    void drawTrisIndexed(const std::vector<point>& points, const std::vector<int>& indices);

    void drawCircle(const point& pos, int radius, const color& c);
    void drawCircles(const std::vector<point>& points, const std::vector<int> radii);  

    void drawCircle(const point& pos, int radius);

    void setDrawColor(const color& c);
};

}