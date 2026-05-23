#ifndef __COLORMANAGER_HPP__
#define __COLORMANAGER_HPP__

#include <string>

struct Color {
    unsigned int r, g, b;
    
    bool operator==(const Color& other) const {
        return r == other.r && g == other.g && b == other.b;
    }

    std::string toSvgFormat() const ;
};

const Color BLACK = {0, 0, 0},
            WHITE = {255, 255, 255},
            RED = {255, 0, 0},
            GREEN = {0, 255, 0},
            BLUE = {0, 0, 255};



#endif