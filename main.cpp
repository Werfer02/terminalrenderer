#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#include "renderScreen.hpp"

int main(){
    std::cout << "Hello, World!\n";
    tr::RenderScreen s(50, 50);

    s.clear();

    s.drawCircle({25, 25}, 18, tr::color::magenta);

    std::vector<tr::vertex> vertices {{{18, 12}, tr::color::red},
                                      {{32, 12}, tr::color::green},
                                      {{10, 25}, tr::color::blue},
                                      {{40, 25}, tr::color::red},
                                      {{18, 38}, tr::color::green},
                                      {{32, 38}, tr::color::blue}};
    std::vector<int> indices {0, 1, 2, 1, 2, 3, 2, 3, 4, 3, 4, 5};
    s.drawPolyIndexed(vertices, indices);

    s.setDrawColor(tr::color::yellow);
    s.drawLines(std::vector<tr::point>{{18, 12}, {32, 12}, {40, 25}, {32, 38}, {18, 38}, {10, 25}});

    s.setDrawColor(tr::color::cyan);
    s.drawCircles(vertices, std::vector<int>(6, 2));

    s.doublePrint();
}