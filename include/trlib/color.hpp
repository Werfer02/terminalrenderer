#pragma once

namespace tr {

struct color{ 
    int r = 0, g = 0, b = 0;
    int a = 255;
    const static color red;
    const static color green;
    const static color blue;
    const static color white;
    const static color cyan;
    const static color magenta;
    const static color yellow;
    const static color black;
};

}