#include "../hpp_files/Rectangle.hpp"
#include "../hpp_files/ColorManager.hpp"
#include <iostream>

Rectangle::Rectangle() : starting_point({0, 0}), width(1), height(1), Shape(BLACK) {}
Rectangle::Rectangle(const Point& point, double width_, double height_, const Color& color_) : Shape(color_), width(width_), height(height_), starting_point(point) {}


// translate the rectangle by x and y
void Rectangle::translate(double dx, double dy) {
    starting_point.x += dx;
    starting_point.y += dy;
}

bool Rectangle::containsPoint(const Point& point) const {
    return (point.x >= starting_point.x && point.x <= starting_point.x + width) &&
           (point.y >= starting_point.y && point.y <= starting_point.y + height);
}

bool Rectangle::within(const Shape& other) const {
    Point p1 = starting_point;
    Point p2 = {starting_point.x + width, starting_point.y};
    Point p3 = {starting_point.x, starting_point.y + height};
    Point p4 = {starting_point.x + width, starting_point.y + height};

    return other.containsPoint(p1) &&
           other.containsPoint(p2) && 
           other.containsPoint(p3) && 
           other.containsPoint(p4);
}

std::string Rectangle::getType() const {
    return "Rectangle";
}

Shape* Rectangle::clone() const {
    return new Rectangle(*this);
}

void Rectangle::print(std::ostream& os) const {
    os << "rectangle " 
       << starting_point.x << " " 
       << starting_point.y << " " 
       << width << " " 
       << height << " " 
       << color.toSvgFormat();
}






