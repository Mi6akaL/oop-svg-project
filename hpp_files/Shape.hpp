#ifndef __SHAPE_HPP
#define __SHAPE_HPP
#include <string>
#include <iostream>
#include <vector>
#include "ColorManager.hpp"

struct Point {
    double x, y;
};

class Shape {
    protected:
        Color color;

    public:
        // Default and parameterized constructors
        Shape();
        Shape(const Color&);

        // Default destructor
        virtual ~Shape() = default;
        
        // translate the shape by dx and dy
        virtual void translate(double, double) = 0;

        // check if the shape is within another shape
        virtual bool within(const Shape&) const = 0;

        // create a copy of the shape
        virtual Shape* clone() const = 0;

        // set the shape's color
        void setColor(const Color&);

        // check if the shape contains a point (x, y)
        virtual bool containsPoint(const Point&) const = 0;

        // get the type of the shape as a string
        virtual std::string getType() const = 0;

        // Convert the printable shape to an SVG tag string
        virtual std::string toSVGtag() const = 0;

        // print the shape's details
        virtual void print(std::ostream&) const = 0;

};

#endif