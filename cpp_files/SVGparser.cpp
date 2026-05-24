#include "../hpp_files/SVGparser.hpp"
#include "../hpp_files/Circle.hpp"
#include "../hpp_files/Rectangle.hpp"
#include "../hpp_files/Ellipses.hpp"
#include "../hpp_files/Line.hpp"
#include "../hpp_files/Polygon.hpp"

// Helper function : Finds the value of an attribute in an SVG tag string.
// Returns "" if attribute is not found
std::string SVGParser::getAttribute(const std::string& tag, const std::string& attr) {
    
    std::string search = attr + "=\"";
    size_t pos = tag.find(search);
    if (pos == std::string::npos) return "";

    pos += search.length();
    size_t end = tag.find("\"", pos);
    if (end == std::string::npos) return "";

    return tag.substr(pos, end - pos);
}

// Parses a rectangle SVG tag and returns a new Rectangle object
Shape* SVGParser::parseRectangle(const std::string& tag) {
    Point p = {
        std::stod(getAttribute(tag, "x")),
        std::stod(getAttribute(tag, "y"))
    };
    double w = std::stod(getAttribute(tag, "width"));
    double h = std::stod(getAttribute(tag, "height"));
    Color  c = Color::SVGtoColor(getAttribute(tag, "fill"));

    return new Rectangle(p, w, h, c);
}