#ifndef __ELLIPSES_HPP
#define __ELLIPSES_HPP
#include "Shape.hpp"

class Ellipse : public Shape {
    protected:
        Point center;
        double radius_x, radius_y;
    public:
        // Default and parameterized constructors
        Ellipse();
        Ellipse(const Point&, double, double, const Color&);

        void translate(double, double) override;
        bool containsPoint(const Point&) const override;
        bool within(const Shape&) const override;
        
        std::string getType() const override;
        
        virtual Shape* clone() const override;

        std::string toSVGtag() const override;
        void print(std::ostream&) const override;

};



#endif