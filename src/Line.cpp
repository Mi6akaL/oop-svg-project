#include "../include/Line.hpp"
#include <cmath>

Line::Line() : start({0, 0}), end({1, 1}), Shape(BLACK) {}

Line::Line(const Point& start_, const Point& end_, const Color& color_) 
    : Shape(color_), start(start_), end(end_) {}

void Line::translate(double dx, double dy) {
    start.x += dx;
    start.y += dy;
    end.x   += dx;
    end.y   += dy;
}

bool Line::containsPoint(const Point& point) const {
    double cross = (end.x - start.x) * (point.y - start.y) - 
                   (end.y - start.y) * (point.x - start.x);

    if (std::abs(cross) > 1e-10) return false; 

    return point.x >= std::min(start.x, end.x) &&
           point.x <= std::max(start.x, end.x) &&
           point.y >= std::min(start.y, end.y) &&
           point.y <= std::max(start.y, end.y);
}

bool Line::within(const Shape& other) const {
    return other.containsPoint(start) && other.containsPoint(end);
}

std::string Line::getType() const {
    return "Line";
}

Shape* Line::clone() const {
    return new Line(*this);
}

std::string Line::toSVGtag() const {
    return "<line x1=\""  + std::to_string(start.x) + 
           "\" y1=\""     + std::to_string(start.y) + 
           "\" x2=\""     + std::to_string(end.x)   + 
           "\" y2=\""     + std::to_string(end.y)   + 
           "\" stroke=\"" + color.colorToSVG()      + "\" />";
}

void Line::print(std::ostream& os) const {
    os << "line " 
       << start.x << " " 
       << start.y << " " 
       << end.x << " " 
       << end.y << " " 
       << color.colorToSVG();
}
