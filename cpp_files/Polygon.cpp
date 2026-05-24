#include "../hpp_files/Polygon.hpp"

Polygon::Polygon() : points({{0, 0}, {1, 0}, {1, 1}}), Shape(BLACK) {}

Polygon::Polygon(const std::vector<Point>& points_, const Color& color_) 
    : Shape(color_), points(points_) {}

void Polygon::translate(double dx, double dy) {
    for (Point& vertex : points) {
        vertex.x += dx;
        vertex.y += dy;
    }
}

bool Polygon::containsPoint(const Point& point) const {
    bool inside = false;
    int n = points.size();
    for (int i = 0 , j = n - 1 ; i < n ; j = i++) {
        bool crossesY = (points[i].y > point.y) != (points[j].y > point.y);
        double xIntersect = (points[j].x - points[i].x) *
                            (point.y - points[i].y) / 
                            (points[j].y - points[i].y) + points[i].x;
        if (crossesY && point.x < xIntersect) {
            inside = !inside;
        }
    }
    return inside;
}

bool Polygon::within(const Shape& other) const {
    for (const Point& p : points) {
        if (!other.containsPoint(p)) return false;
    }
    return true;
}

std::string Polygon::getType() const {
    return "Polygon";
}

Shape* Polygon::clone() const {
    return new Polygon(*this);
}

void Polygon::print(std::ostream& os) const {
    os << "polygon " 
       << points.size() << " ";
    for (const Point& p : points) {
        os << p.x << " " << p.y << " ";
    }
    os << color.colorToSVG();
}