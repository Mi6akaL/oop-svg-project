#include "../hpp_files/Rectangle.hpp"
#include "../hpp_files/ColorManager.hpp"
#include <iostream>

Rect::Rect() : starting_point({0, 0}), width(1), height(1), Shape(BLACK) {}
Rect::Rect(const Point& point, double width_, double height_, const Color& color_) : Shape(color_), width(width_), height(height_), starting_point(point) {}


// translate the rectangle by x and y
void Rect::translate(double dx, double dy) {
    starting_point.x += dx;
    starting_point.y += dy;
}

bool Rect::containsPoint(const Point& point) const {
    return (point.x >= starting_point.x && point.x <= starting_point.x + width) &&
           (point.y >= starting_point.y && point.y <= starting_point.y + height);
}

bool Rect::within(const Shape& other) const {
    Point p1 = starting_point;
    Point p2 = {starting_point.x + width, starting_point.y};
    Point p3 = {starting_point.x, starting_point.y + height};
    Point p4 = {starting_point.x + width, starting_point.y + height};

    return other.containsPoint(p1) &&
           other.containsPoint(p2) && 
           other.containsPoint(p3) && 
           other.containsPoint(p4);
}

std::string Rect::getType() const {
    return "Rectangle";
}

Shape* Rect::clone() const {
    return new Rect(*this);
}

std::string Rect::toSVGtag() const {
    return "<rect x=\""    + std::to_string(starting_point.x) + 
           "\" y=\""       + std::to_string(starting_point.y) + 
           "\" width=\""   + std::to_string(width)            + 
           "\" height=\""  + std::to_string(height)           + 
           "\" fill=\""    + color.colorToSVG()               + "\" />";
}

void Rect::print(std::ostream& os) const {
    os << "rectangle " 
       << starting_point.x << " " 
       << starting_point.y << " " 
       << width << " " 
       << height << " " 
       << color.colorToSVG();
}






