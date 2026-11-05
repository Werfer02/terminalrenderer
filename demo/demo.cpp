#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#define STB_IMAGE_IMPLEMENTATION

#include "renderScreen.hpp"
#include "stb_image.h"

#include "color.hpp"

int main(){
    std::cout << "Hello, World!\n";

    tr::RenderScreen s(70, 70);

    s.clear(tr::color::yellow);

    s.drawLine({{4, 20}, {255, 127, 0}}, {{58, 20}, {127, 0, 255}});

    std::vector<tr::point> circlePositions {{10, 10}, {30, 10}, {50, 10}};
    std::vector<int> circleRadii {6, 7, 8};
    s.setDrawColor(tr::color::green);
    s.drawCircles(circlePositions, circleRadii);

    std::vector<tr::vertex> polyVertices {{{11, 23}, tr::color::red},
                                          {{25, 23}, tr::color::green},
                                          {{3, 36}, tr::color::blue},
                                          {{33, 36}, tr::color::blue},
                                          {{11, 49}, tr::color::green},
                                          {{25, 49}, tr::color::red}};
    std::vector<int> polyIndices {0, 1, 2, 1, 2, 3, 2, 3, 4, 3, 4, 5};
    s.drawPolyIndexed(polyVertices, polyIndices);

    std::vector<tr::point> linePoints {{43, 23},
                                       {57, 23},
                                       {65, 36},
                                       {57, 49},
                                       {43, 49},
                                       {35, 36}};
    s.setDrawColor(tr::color::red);
    s.drawLines(linePoints);

    tr::texture t;
    t.data = stbi_load("demo/alpha.png", &t.w, &t.h, &t.channels, 0);
    std::vector<tr::vertex> v2 {{{10, 50}, {}, {0, 0}},
                                {{45, 50}, {}, {1, 0}},
                                {{10, 66}, {}, {0, 1}},
                                {{45, 66}, {}, {1, 1}}};
    std::vector<int> i2 {0, 1, 2, 1, 2, 3};
    s.drawPolyIndexed(v2, i2, t);
    s.doublePrint();
    stbi_image_free(t.data);
}