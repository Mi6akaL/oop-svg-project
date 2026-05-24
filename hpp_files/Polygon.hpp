#ifndef __POLYGON_HPP
#define __POLYGON_HPP
#include "Shape.hpp"

class Polygon : public Shape {
    protected:
        std::vector<Point> points;
    public:
        // Default and parameterized constructors
        Polygon();
        Polygon(const std::vector<Point>&, const Color&);

        void translate(double, double) override;
        bool containsPoint(const Point&) const override;
        bool within(const Shape&) const override;
        
        std::string getType() const override;
        
        virtual Shape* clone() const override;

        void print(std::ostream&) const override;

};


#endif