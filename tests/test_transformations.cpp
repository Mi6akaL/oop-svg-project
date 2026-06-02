#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../include/Rect.hpp"
#include "../include/Circle.hpp"
#include "../include/Line.hpp"

// Компилация: g++ tests/test_transformations.cpp src/*.cpp -o tests/run_transformations

TEST_CASE("Shapes identify their type correctly") {
    Rect r(Point{0, 0}, 5, 5, RED);
    Circle c(Point{0, 0}, 10, BLUE);
    Line l(Point{0, 0}, Point{5, 5}, GREEN);

    CHECK(r.getType() == "Rectangle");
    CHECK(c.getType() == "Circle");
    CHECK(l.getType() == "Line");
}

TEST_CASE("Translation works correctly for different shapes") {
    SUBCASE("Rectangle translation") {
        Rect rect(Point{10, 20}, 5, 5, RED);
        rect.translate(5, -10);
        CHECK(rect.containsPoint(Point{15, 10}) == true);
        CHECK(rect.containsPoint(Point{10, 20}) == false);
    }

    SUBCASE("Circle translation") {
        Circle circle(Point{0, 0}, 5, BLUE);
        circle.translate(10, 10);
        CHECK(circle.containsPoint(Point{10, 10}) == true); // Center after translation
        CHECK(circle.containsPoint(Point{0, 0}) == false);  // Old center should no longer be contained
    }

    SUBCASE("Line translation") {
        Line line(Point{0, 0}, Point{2, 2}, GREEN);
        line.translate(1, 1);
        CHECK(line.containsPoint(Point{1, 1}) == true); // New starting point
        CHECK(line.containsPoint(Point{3, 3}) == true); // New ending point
    }
}