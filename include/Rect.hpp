#ifndef __RECTANGLE_HPP
#define __RECTANGLE_HPP
#include "Shape.hpp"

class Rect : public Shape {
    protected:
        Point starting_point;
        double width, height;
    public:
        // Default and parameterized constructors
        Rect();
        Rect(const Point&, double, double, const Color&);

        void translate(double, double) override;
        bool containsPoint(const Point&) const override;
        bool within(const Shape&) const override;
        
        std::string getType() const override;

        virtual Shape* clone() const override;

        std::string toSVGtag() const override;
        void print(std::ostream&) const override;

};














#endif