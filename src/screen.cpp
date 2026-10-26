#include "screen.hpp"

#include <iostream>

#include "coututils.hpp"

namespace tr {

Screen::Screen() {
    data = std::vector<std::string>(width*height, " ");
}
Screen::Screen(int w, int h) : width(w), height(h) {
    data = std::vector<std::string>(width*height, " ");
}	
void Screen::clear(){
    data = std::vector<std::string>(width*height, " ");
}
void Screen::clear(const color& c){
    data = std::vector<std::string>(width*height, ansi::rgb(c.r, c.g, c.b) + "█");
}
void Screen::putPixel(const point& p, const std::string& s){
    data[(p.y * width) + p.x] = s;
}
void Screen::putPixel(const point& p, const color& c){
    data[(p.y * width) + p.x] = ansi::rgb(c.r, c.g, c.b) + "█";
}
void Screen::print(){
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            std::cout << data[(i*width) + j] << ansi::reset;
        }
        std::cout << "\n";
    }
}
void Screen::doublePrint(){
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            std::cout << data[(i*width) + j] << data[(i*width) + j] << ansi::reset;
        }
        std::cout << "\n";
    }
}

}