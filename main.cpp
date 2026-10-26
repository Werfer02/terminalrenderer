#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#define STB_IMAGE_IMPLEMENTATION

#include "renderScreen.hpp"
#include "stb_image.h"

int main(){
    std::cout << "Hello, World!\n";
    tr::RenderScreen s(100, 100);

    s.clear(tr::color::white);

    s.drawCircle({25, 25}, 18, tr::color::magenta);

    std::vector<tr::vertex> vertices {{{18, 12}, tr::color::red},
                                      {{32, 12}, tr::color::green},
                                      {{10, 25}, tr::color::blue},
                                      {{40, 25}, tr::color::blue},
                                      {{18, 38}, tr::color::green},
                                      {{32, 38}, tr::color::red}};
    std::vector<int> indices {0, 1, 2, 1, 2, 3, 2, 3, 4, 3, 4, 5};
    s.drawPolyIndexed(vertices, indices);

    s.setDrawColor(tr::color::yellow);
    s.drawLines(std::vector<tr::point>{{18, 12}, {32, 12}, {40, 25}, {32, 38}, {18, 38}, {10, 25}});

    s.setDrawColor(tr::color::cyan);
    s.drawCircles(vertices, std::vector<int>(6, 2));

    tr::texture t;
    t.data = stbi_load(".vscode/watermark.png", &t.w, &t.h, &t.channels, 0);
    std::vector<tr::vertex> v2 {{{10, 50}, {}, {0, 0}},
                                {{90, 50}, {}, {1, 0}},
                                {{10, 80}, {}, {0, 1}},
                                {{90, 80}, {}, {1, 1}}};
    std::vector<int> i2 {0, 1, 2, 1, 2, 3};
    s.drawPolyIndexed(v2, i2, t);
    int a = 5;
    s.doublePrint();
    stbi_image_free(t.data);
}