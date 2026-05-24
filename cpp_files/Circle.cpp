#include "../hpp_files/Circle.hpp"
#include <cmath>


Circle::Circle() : center({0, 0}), radius(1), Shape(BLACK) {}

Circle::Circle(const Point& center_, const double& radius_, const Color& color_) 
    : Shape(color_), center(center_), radius(radius_) {}

void Circle::translate(double dx, double dy) {
    center.x += dx;
    center.y += dy;
}

bool Circle::containsPoint(const Point& point) const {
    double dx = point.x - center.x;
    double dy = point.y - center.y;
    return (dx * dx + dy * dy) <= (radius * radius);
}

bool Circle::within(const Shape& other) const {

    Point top    = {center.x, center.y - radius};
    Point bottom = {center.x, center.y + radius};
    Point left   = {center.x - radius, center.y};
    Point right  = {center.x + radius, center.y};

    return other.containsPoint(top)    &&
           other.containsPoint(bottom) && 
           other.containsPoint(left)   && 
           other.containsPoint(right);
}

std::string Circle::getType() const {
    return "Circle";
}

Shape* Circle::clone() const {
    return new Circle(*this);
}

std::string Circle::toSVGtag() const {
    return "<circle cx=\"" + std::to_string(center.x) + 
           "\" cy=\""      + std::to_string(center.y) + 
           "\" r=\""       + std::to_string(radius)   + 
           "\" fill=\""    + color.colorToSVG()       + "\" />";
}

void Circle::print(std::ostream& os) const {
    os << "circle " 
       << center.x << " " 
       << center.y << " " 
       << radius << " " 
       << color.colorToSVG();
}