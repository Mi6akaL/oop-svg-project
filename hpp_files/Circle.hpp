#ifndef __CIRCLE_HPP
#define __CIRCLE_HPP
#include "Shape.hpp"
#include <cmath>

class Circle : public Shape {
    protected:
        Point center;
        double radius;
    public:
        // Default and parameterized constructors
        Circle();
        Circle(const Point&, const double&, const Color&);

        void translate(double, double) override;
        bool containsPoint(const Point&) const override;
        bool within(const Shape&) const override;
        
        std::string getType() const override;

        virtual Shape* clone() const override;

        std::string toSVGtag() const override;
        void print(std::ostream&) const override;

};


#endif