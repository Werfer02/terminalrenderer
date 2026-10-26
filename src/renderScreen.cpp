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
        color c = {(int)(start.c.r*(1 - progress) + end.c.r*progress),
                   (int)(start.c.g*(1 - progress) + end.c.g*progress),
                   (int)(start.c.b*(1 - progress) + end.c.b*progress)};
        putPixel(effectivepos, c);
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

template <typename f>
void forEachInTri(const vertex& p1, const vertex& p2, const vertex& p3, f&& todo){
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
                todo(i, j, w1, w2, w3);
            }
        }
    }
}

color blend(const color& c1, const color& c2, float w){
    return {c1.r*w + c2.r*(1-w),
            c1.g*w + c2.g*(1-w),
            c1.b*w + c2.b*(1-w)};
}

void RenderScreen::drawTri(const vertex& p1, const vertex& p2, const vertex& p3){

    auto drawWithAvgColor = [&] (int i, int j, float w1, float w2, float w3){
        int r = (w1*p1.c.r + w2*p2.c.r + w3*p3.c.r);
        int g = (w1*p1.c.g + w2*p2.c.g + w3*p3.c.g);
        int b = (w1*p1.c.b + w2*p2.c.b + w3*p3.c.b);
        int a = (w1*p1.c.a + w2*p2.c.a + w3*p3.c.a);
        putPixel({j, i}, blend({r, g, b}, colors[i*width + j], (float)a/255.f));
    };
    
    forEachInTri(p1, p2, p3, drawWithAvgColor);
}

void RenderScreen::drawTri(const point& p1, const point& p2, const point& p3){
    auto drawWithDrawColor = [&] (int i, int j, float w1, float w2, float w3){
        putPixel({j, i}, drawColor);
    };
    
    forEachInTri(p1, p2, p3, drawWithDrawColor);
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

bool sortVertices(const vertex& a, const vertex& b){
    if(a.y < b.y) return true;
    if(a.y == b.y && a.x < b.x) return true;
    return false;
}

void RenderScreen::drawPoly(std::vector<vertex> vertices){
    std::sort(vertices.begin(), vertices.end(), sortVertices);
    auto drawWithAvgColor = [&](int i, int j, float w1, float w2, float w3){
        float totalWeights = 0;
        color c = {0, 0, 0};
        for(const auto& v : vertices){
            float mag = vec2D(vec2D{(float)j, (float)i} - vec2D(v)).mag();
            float weight = 1/mag;
            
            totalWeights += weight;

            c.r += v.c.r * weight;
            c.g += v.c.g * weight;
            c.b += v.c.b * weight;
            c.a += v.c.a * weight;
        }

        c.r /= totalWeights;
        c.g /= totalWeights;
        c.b /= totalWeights;
        c.a /= totalWeights;
        putPixel({j, i}, blend(c, colors[i*width + j], (float)c.a/255.f));
    };
    for(int i = 0; i < vertices.size() - 2; i+=3){

        forEachInTri(vertices[i], vertices[i+1], vertices[i+2], drawWithAvgColor);

    }
}

void RenderScreen::drawPoly(std::vector<vertex> vertices, const texture& t){
    std::sort(vertices.begin(), vertices.end(), sortVertices);
    for(int i = 0; i < vertices.size() - 2; i+=3){

        auto drawWithTexture = [&](int ini, int j, float w1, float w2, float w3){
            float totalWeights = 0;

            float tx = vertices[i].uv.x*w1 + vertices[i+1].uv.x*w2 + vertices[i+2].uv.x*w3;
            tx = std::clamp(int(tx * t.w), 0, t.w - 1);
            float ty = vertices[i].uv.y*w1 + vertices[i+1].uv.y*w2 + vertices[i+2].uv.y*w3;
            ty = std::clamp(int(ty * t.h), 0, t.h - 1);

            int offset = (ty * t.w + tx) * t.channels;

            int r = t.data[offset];
            int g = t.data[offset + 1];
            int b = t.data[offset + 2];
            
            int a = t.channels >= 4 ? t.data[offset + 3] : 255;
            putPixel({j, ini}, blend({r, g, b}, colors[ini*width + j], (float)a/255.f));
        };

        forEachInTri(vertices[i], vertices[i+1], vertices[i+2], drawWithTexture);

    }
}


void RenderScreen::drawPolyIndexed(const std::vector<vertex>& vertices, const std::vector<int>& indices){
    std::vector<vertex> sorted = vertices;
    std::sort(sorted.begin(), sorted.end(), sortVertices);
    auto drawWithAvgColor = [&](int i, int j, float w1, float w2, float w3){
        float totalWeights = 0;
        color c = {0, 0, 0, 0};
        for(const auto& v : sorted){
            float mag = vec2D(vec2D{(float)j, (float)i} - vec2D(v)).mag();
            float weight = 1/mag;
            
            totalWeights += weight;

            c.r += v.c.r * weight;
            c.g += v.c.g * weight;
            c.b += v.c.b * weight;
            c.a += v.c.a * weight;
        }


        c.r /= totalWeights;
        c.g /= totalWeights;
        c.b /= totalWeights;
        c.a /= totalWeights;
        putPixel({j, i}, blend(c, colors[i*width + j], (float)c.a/255.f));
    };
    for(int i = 0; i < indices.size() - 2; i+=3){

        forEachInTri(vertices[indices[i]], vertices[indices[i+1]], vertices[indices[i+2]], drawWithAvgColor);

    }
}

void RenderScreen::drawPolyIndexed(const std::vector<vertex>& vertices, const std::vector<int>& indices, const texture& t){
    for(int i = 0; i < indices.size() - 2; i+=3){

        auto drawWithTexture = [&](int ini, int j, float w1, float w2, float w3){
            float totalWeights = 0;

            float tx = vertices[indices[i]].uv.x*w1 + vertices[indices[i+1]].uv.x*w2 + vertices[indices[i+2]].uv.x*w3;
            tx = std::clamp(int(tx * t.w), 0, t.w - 1);
            float ty = vertices[indices[i]].uv.y*w1 + vertices[indices[i+1]].uv.y*w2 + vertices[indices[i+2]].uv.y*w3;
            ty = std::clamp(int(ty * t.h), 0, t.h - 1);

            int offset = (ty * t.w + tx) * t.channels;

            int r = t.data[offset];
            int g = t.data[offset + 1];
            int b = t.data[offset + 2];

            int a = t.channels >= 4 ? t.data[offset + 3] : 255;
            putPixel({j, ini}, blend({r, g, b}, colors[ini*width + j], (float)a/255.f));
        };

        forEachInTri(vertices[indices[i]], vertices[indices[i+1]], vertices[indices[i+2]], drawWithTexture);

    }
}

void RenderScreen::drawPoly(std::vector<point> points){
    std::sort(points.begin(), points.end(), sortVertices);
    auto drawWithDrawColor = [&](int i, int j, float w1, float w2, float w3){
        putPixel({j, i}, drawColor);
    };
    for(int i = 0; i < points.size() - 2; i++){
        forEachInTri(points[i], points[i+1], points[i+2], drawWithDrawColor);
    }
}

void RenderScreen::drawPolyIndexed(const std::vector<point>& points, const std::vector<int>& indices){
    auto drawWithDrawColor = [&](int i, int j, float w1, float w2, float w3){
        putPixel({j, i}, drawColor);
    };
    for(int i = 0; i < points.size() - 2; i++){
        forEachInTri(points[i], points[i+1], points[i+2], drawWithDrawColor);
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
            if(relx*relx + rely*rely <= radius*radius) putPixel({j, i}, c);
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

void RenderScreen::drawCircles(const std::vector<vertex>& vertices, const std::vector<int> radii){
    for(int i = 0; i < vertices.size(); i++){
        drawCircle(vertices[i], radii[i]);
    }
}

void RenderScreen::setDrawColor(const color& c){
    drawColor = c;
}

}