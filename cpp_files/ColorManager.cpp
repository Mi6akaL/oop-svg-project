#include "../hpp_files/ColorManager.hpp"

std::string Color::toSvgFormat() const {
    return "rgb(" + std::to_string(r) + "," + 
                    std::to_string(g) + "," + 
                    std::to_string(b) + ")";
}