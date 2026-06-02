#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../include/Rect.hpp"
#include "../include/Circle.hpp"

// Компилация: g++ tests/test_geometry.cpp src/*.cpp -o tests/run_geometry

TEST_CASE("containsPoint checks boundaries correctly") {
    SUBCASE("Rectangle boundaries") {
        Rect rect(Point{0, 0}, 10, 5, RED);
        CHECK(rect.containsPoint(Point{5, 2.5}) == true); // Inside
        CHECK(rect.containsPoint(Point{0, 0}) == true);   // Corner
        CHECK(rect.containsPoint(Point{11, 3}) == false);  // Outside
    }

    SUBCASE("Circle boundaries") {
        Circle circle(Point{0, 0}, 5, BLUE);
        CHECK(circle.containsPoint(Point{0, 0}) == true);   // Center
        CHECK(circle.containsPoint(Point{3, 4}) == true);   // Exactly on the boundary (3^2 + 4^2 = 5^2)
        CHECK(circle.containsPoint(Point{5, 1}) == false);  // A little outside the circle
    }
}

TEST_CASE("within detects nesting correctly") {
    Rect big_rect(Point{0, 0}, 20, 20, BLACK);
    Rect small_rect(Point{2, 2}, 5, 5, RED);
    Rect outside_rect(Point{15, 15}, 10, 10, GREEN);

    CHECK(small_rect.within(big_rect) == true);
    CHECK(outside_rect.within(big_rect) == false);

    Circle inner_circle(Point{5, 5}, 3, BLUE);
    CHECK(inner_circle.within(big_rect) == true);
}