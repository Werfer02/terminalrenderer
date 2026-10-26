#include "screen.hpp"

#include <iostream>

#include "coututils.hpp"

namespace tr {

Screen::Screen() {
    characters = std::u32string(width*height, U' ');
    colors = std::vector<color>(width*height);
}
Screen::Screen(int w, int h) : width(w), height(h) {
    characters = std::u32string(width*height, U' ');
    colors = std::vector<color>(width*height);
}	
void Screen::clear(){
    characters = std::u32string(width*height, U' ');
    colors = std::vector<color>(width*height);
}
void Screen::clear(const color& c){
    characters = std::u32string(width*height, U'█');
    colors = std::vector<color>(width*height, c);
}
void Screen::putChar(const point& p, char32_t s){
    characters[(p.y * width) + p.x] = s;
}
void Screen::putPixel(const point& p, const color& c){
    characters[(p.y * width) + p.x] = U'█';
    colors[(p.y * width) + p.x] = c;
}

void appendUTF8(std::string& out, char32_t c){
    if (c <= 0x7F) out.push_back(char(c)); // normal char
    else if (c <= 0x7FF){ // two byte char
        out.push_back(char(0xC0 | (c >> 6)));   // prefix + top bits
        out.push_back(char(0x80 | (c & 0x3F))); // prefix + bottom 6 bits
    }
    else if (c <= 0xFFFF) { // three byte char
        out.push_back(char(0xE0 | (c >> 12)));         // prefix + top bits
        out.push_back(char(0x80 | ((c >> 6) & 0x3F))); // prefix + middle bits
        out.push_back(char(0x80 | (c & 0x3F)));        // prefix + bottom bits
    }
    else if (c <= 0x10FFFF) { // four byte char
        out.push_back(char(0xF0 | (c >> 16)));          // prefix + top bits
        out.push_back(char(0x80 | ((c >> 12) & 0x3F))); // prefix + middle bits
        out.push_back(char(0x80 | ((c >> 6) & 0x3F)));  // prefix + middle bits
        out.push_back(char(0x80 | (c & 0x3F)));         // prefix + bottom bits
    }
}
void Screen::print(){
    std::string output;
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            const color& c = colors[i*width + j];
            output.append(ansi::rgb(c.r, c.g, c.b));
            appendUTF8(output, characters[i*width + j]);
            output.append(ansi::reset);
        }
        output.push_back('\n');
    }
    std::cout << output;
}
void Screen::doublePrint(){
    std::string output;
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            const color& c = colors[i*width + j];
            output.append(ansi::rgb(c.r, c.g, c.b));
            appendUTF8(output, characters[i*width + j]);
            appendUTF8(output, characters[i*width + j]);
            output.append(ansi::reset);
        }
        output.push_back('\n');
    }
    std::cout << output;
}

}