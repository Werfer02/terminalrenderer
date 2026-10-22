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

    s.setDrawColor(tr::color::red);
    std::vector<tr::vertex> vertices {{{18, 12}, tr::color::green},
                                      {{32, 12}, tr::color::cyan},
                                      {{10, 25}, tr::color::white},
                                      {{40, 25}, tr::color::black},
                                      {{18, 38}, {220, 110, 10}},
                                      {{32, 38}, {10, 110, }}};
    std::vector<int> indices {0, 1, 2, 1, 2, 3, 2, 3, 4, 3, 4, 5};
    s.drawTrisIndexed(vertices, indices);

    s.setDrawColor(tr::color::yellow);
    s.drawLines(std::vector<tr::point>{{18, 12}, {32, 12}, {40, 25}, {32, 38}, {18, 38}, {10, 25}});

    s.setDrawColor(tr::color::blue);
    s.drawCircles(vertices, std::vector<int>(6, 2));

    s.doublePrint();
}