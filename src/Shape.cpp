#include "../include/Shape.hpp"

Shape::Shape() : color(BLACK) {}
Shape::Shape(const Color& color_) : color(color_) {}

void Shape::setColor(const Color& new_color) {
    color = new_color;
}





