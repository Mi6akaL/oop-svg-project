#ifndef __LINE_HPP
#define __LINE_HPP
#include "Shape.hpp"

class Line : public Shape {
    protected:
        Point start, end;
    public:
        // Default and parameterized constructors
        Line();
        Line(const Point&, const Point&, const Color&);

        void translate(double, double) override;
        bool containsPoint(const Point&) const override;
        bool within(const Shape&) const override;
        
        std::string getType() const override;
        
        virtual Shape* clone() const override;

        std::string toSVGtag() const override;
        void print(std::ostream&) const override;
};



#endif