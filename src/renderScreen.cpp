#include "renderScreen.hpp"

#include <algorithm>
#include <iostream>
#include <cmath>

#include "vec2D.hpp"
#include "coututils.hpp"

namespace tr {

void RenderScreen::drawLine(vertex start, vertex end){

    bool flipy = false;
    bool flipxy = false;

    if(start.x > end.x){
        std::swap(start, end);
    }
    point offset = start;

    float slope = (end.y - start.y) / float(end.x - start.x);

    if(slope < 0) {
        std::swap(start.y, end.y);
        slope = -slope;
        flipy = true;
    }
    
    if(slope > 1){
        slope = 1 / slope;
        std::swap(start.x, start.y);
        std::swap(end.x, end.y);
        flipxy = true;
    }

    int y = 0;
    for(int x = 0; x <= (end.x - start.x); x++){
        float stayError = std::abs(y - (x*slope));
        float addError = std::abs((y + 1) - (x*slope));
        if(addError < stayError) y++;

        point effectivepos = {x, y};
        if(flipxy) std::swap(effectivepos.x, effectivepos.y);
        if(flipy) effectivepos.y *= -1;

        effectivepos += offset;

        float progress = ((float)x / (end.x - start.x));
        color c = {start.c.r*(1 - progress) + end.c.r*progress,
                   start.c.g*(1 - progress) + end.c.g*progress,
                   start.c.b*(1 - progress) + end.c.b*progress};
        data[((effectivepos.y) * width) + effectivepos.x] = ansi::rgb(c.r, c.g, c.b) + "█";
    }
}

void RenderScreen::drawLine(point start, point end){
    drawLine({start, drawColor}, {end, drawColor});
}

void RenderScreen::drawLines(const std::vector<vertex>& vertices){
    for(int i = 0; i < vertices.size(); i++){
        if(i == (vertices.size() - 1)){
            drawLine(vertices[i], vertices[0]);
        } else drawLine(vertices[i], vertices[i+1]);
    }
}

void RenderScreen::drawLines(const std::vector<point>& points){
    for(int i = 0; i < points.size(); i++){
        if(i == (points.size() - 1)){
            drawLine(points[i], points[0]);
        } else drawLine(points[i], points[i+1]);
    }
}

void RenderScreen::drawTri(const vertex& p1, const vertex& p2, const vertex& p3){
    float minx = std::min({p1.x, p2.x, p3.x});
    float miny = std::min({p1.y, p2.y, p3.y});
    float maxx = std::max({p1.x, p2.x, p3.x});
    float maxy = std::max({p1.y, p2.y, p3.y});

    vec2D up = p2 - p1;
    vec2D right = p3 - p1;
    
    for(int i = miny; i < maxy; i++){
        for(int j = minx; j < maxx; j++){
            vec2D p = {(float)j, (float)i};
            vec2D local = vec2D::toLocal(p, p1, up, right);
            float w2 = local.x;
            float w3 = local.y;
            float w1 = 1 - w2 - w3;
            if(w1 >= 0 && w2 >= 0 && w3 >= 0){
                int r = (w1*p1.c.r + w2*p2.c.r + w3*p3.c.r);
                int g = (w1*p1.c.g + w2*p2.c.g + w3*p3.c.g);
                int b = (w1*p1.c.b + w2*p2.c.b + w3*p3.c.b);
                data[((i) * width) + j] = ansi::rgb(r, g, b) + "█";
            }
        }
    }
}

void RenderScreen::drawTri(const point& p1, const point& p2, const point& p3){
    drawTri({p1, drawColor}, {p2, drawColor}, {p3, drawColor});
}

void RenderScreen::drawTris(const std::vector<vertex>& vertices){
    if(vertices.size() % 3 != 0){
        std::cout << "invalid number of vertices for drawtris";
        return;
    }
    for(int i = 0; i < vertices.size() - 2; i+=3){
        drawTri(vertices[i], vertices[i+1], vertices[i+2]);
    }
}

void RenderScreen::drawTris(const std::vector<point>& points){
    if(points.size() % 3 != 0){
        std::cout << "invalid number of vertices for drawtris";
        return;
    }
    for(int i = 0; i < points.size() - 2; i+=3){
        drawTri(points[i], points[i+1], points[i+2]);
    }
}

void RenderScreen::drawTrisIndexed(const std::vector<point>& points, const std::vector<int>& indices){
    if(indices.size() % 3 != 0){
        std::cout << "invalid number of points for drawtris";
        return;
    }
    for(int i = 0; i < indices.size() - 2; i+=3){
        drawTri(points[indices[i]], points[indices[i+1]], points[indices[i+2]]);
    }
}

void RenderScreen::drawTrisIndexed(const std::vector<vertex>& vertices, const std::vector<int>& indices){
    if(indices.size() % 3 != 0){
        std::cout << "invalid number of points for drawtris";
        return;
    }
    for(int i = 0; i < indices.size() - 2; i+=3){
        drawTri(vertices[indices[i]], vertices[indices[i+1]], vertices[indices[i+2]]);
    }
}

void RenderScreen::drawCircle(const point& pos, int radius, const color& c){
    int minx = std::max(pos.x - radius, 0);
    int miny = std::max(pos.y - radius, 0);
    int maxx = std::min(pos.x + radius, width);
    int maxy = std::min(pos.y + radius, height);

    for(int i = miny; i <= maxy; i++){
        for(int j = minx; j <= maxx; j++){
            int relx = j - minx - radius;
            int rely = i - miny - radius;
            if(relx*relx + rely*rely <= radius*radius) data[((i) * width) + j] = ansi::rgb(c.r, c.g, c.b) + "█";
        }
    }
}

void RenderScreen::drawCircle(const point& pos, int radius){
    drawCircle(pos, radius, drawColor);
}

void RenderScreen::drawCircles(const std::vector<point>& points, const std::vector<int> radii){
    for(int i = 0; i < points.size(); i++){
        drawCircle(points[i], radii[i]);
    }
}

void RenderScreen::setDrawColor(const color& c){
    drawColor = c;
}

}