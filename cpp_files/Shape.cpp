#include "../hpp_files/Shape.hpp"

Shape::Shape() : color(BLACK) {}
Shape::Shape(const Color& color_) : color(color_) {}

void Shape::setColor(const Color& color_) {
    color = color_;
}





