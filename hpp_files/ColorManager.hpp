#ifndef __COLORMANAGER_HPP
#define __COLORMANAGER_HPP

#include <string>

struct Color {
    unsigned int r, g, b;
    
    bool operator==(const Color& other) const {
        return r == other.r && g == other.g && b == other.b;
    }

    std::string colorToSVG() const;
    static Color SVGtoColor(const std::string&);
};

inline const Color BLACK = {0, 0, 0},
            WHITE = {255, 255, 255},
            RED = {255, 0, 0},
            GREEN = {0, 255, 0},
            BLUE = {0, 0, 255};



#endif