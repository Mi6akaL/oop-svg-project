#include "../hpp_files/Ellipses.hpp"

Ellipse::Ellipse() : center({0, 0}), radius_x(1), radius_y(1), Shape(BLACK) {}
Ellipse::Ellipse(const Point& center_, double radius_x_, double radius_y_, const Color& color_) 
    : Shape(color_), center(center_), radius_x(radius_x_), radius_y(radius_y_) {}

void Ellipse::translate(double dx, double dy) {
    center.x += dx;
    center.y += dy;
}

bool Ellipse::containsPoint(const Point& point) const {
    double dx = (point.x - center.x) / radius_x;
    double dy = (point.y - center.y) / radius_y;
    return (dx * dx + dy * dy) <= 1.0;
}

bool Ellipse::within(const Shape& other) const {
    Point top    = {center.x, center.y - radius_y};
    Point bottom = {center.x, center.y + radius_y};
    Point left   = {center.x - radius_x, center.y};
    Point right  = {center.x + radius_x, center.y};

    return other.containsPoint(top)    &&
           other.containsPoint(bottom) && 
           other.containsPoint(left)   && 
           other.containsPoint(right);
}

std::string Ellipse::getType() const {
    return "Ellipse";
}

Shape* Ellipse::clone() const {
    return new Ellipse(*this);
}

std::string Ellipse::toSVGtag() const {
    return "<ellipse cx=\"" + std::to_string(center.x) + 
           "\" cy=\""       + std::to_string(center.y) + 
           "\" rx=\""       + std::to_string(radius_x) + 
           "\" ry=\""       + std::to_string(radius_y) + 
           "\" fill=\""     + color.colorToSVG()       + "\" />";
}

void Ellipse::print(std::ostream& os) const {
    os << "ellipse " 
       << center.x << " " 
       << center.y << " " 
       << radius_x << " " 
       << radius_y << " " 
       << color.colorToSVG();
}