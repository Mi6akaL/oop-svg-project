#include "../hpp_files/ColorManager.hpp"
#include <algorithm>
#include <sstream>
#include <stdexcept>

std::string Color::colorToSVG() const {
    return "rgb(" + std::to_string(r) + "," + 
                    std::to_string(g) + "," + 
                    std::to_string(b) + ")";
}

Color Color::SVGtoColor(const std::string& str) {
    
    std::string s = str;
    s.erase(0, s.find_first_not_of(" \t"));
    s.erase(s.find_last_not_of(" \t") + 1);

    std::string lower = s;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

    // Format 1 - Named Colors
    if (lower == "black") return BLACK;
    if (lower == "white") return WHITE;
    if (lower == "red")   return RED;
    if (lower == "green") return GREEN;
    if (lower == "blue")  return BLUE;

    // Format 2 - Hex Colors (#RRGGBB or #RGB);
    if (s[0] == '#') {
        unsigned int hex;
        std::stringstream ss;
        ss << std::hex << s.substr(1);
        ss >> hex;

        if (s.length() == 7) {
            return { (hex >> 16) & 0xFF, 
                     (hex >> 8)  & 0xFF, 
                     hex         & 0xFF };
        }
        if (s.length() == 4) {
            unsigned int r = (hex >> 8) & 0xF;
            unsigned int g = (hex >> 4) & 0xF;
            unsigned int b =  hex       & 0xF;
            return { r * 17, g * 17, b * 17 };
        }
        throw std::invalid_argument("Invalid hex color format" + str);
    }

    // Format 3 - RGB Colors (rgb(r, g, b));
    if (lower.substr(0, 4) == "rgb(") {
        unsigned int r, g, b;
        char dummy;
        std::stringstream ss(s.substr(4));
        ss >> r >> dummy >> g >> dummy >> b;
        return {r, g, b};
    }

    throw std::invalid_argument("Unknown color format: " + str);
}