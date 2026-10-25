#pragma once

namespace tr {

struct texture {
    int w, h;
    int channels = 3;
    unsigned char* data = nullptr;
};

}