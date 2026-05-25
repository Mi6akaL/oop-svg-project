#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "../hpp_files/Shape.hpp"
#include "../hpp_files/Circle.hpp"
#include "../hpp_files/Rectangle.hpp"
#include "../hpp_files/Ellipses.hpp"
#include "../hpp_files/Line.hpp"
#include "../hpp_files/Polygon.hpp"
#include "../hpp_files/ColorManager.hpp"

TEST_CASE("SVGtoColor parses all three formats correctly") {
    CHECK(Color::SVGtoColor("red")              == RED);
    CHECK(Color::SVGtoColor("RED")              == RED);
    CHECK(Color::SVGtoColor("#ff0000")        == RED);
    CHECK(Color::SVGtoColor("#f00")           == RED);
    CHECK(Color::SVGtoColor("rgb(255, 0, 0)") == RED);
    CHECK(Color::SVGtoColor(" rgb(0,0,0) ")   == BLACK);
}

TEST_CASE("colorToSVG produces correct output") {
    CHECK(RED.colorToSVG() == "rgb(255,0,0)");
    CHECK(BLACK.colorToSVG() == "rgb(0,0,0)");
    CHECK(WHITE.colorToSVG() == "rgb(255,255,255)");
}

TEST_CASE("Rectangle containsPoint works correctly") {
    Rect rect(Point{0, 0}, 10, 5, RED);
    CHECK( rect.containsPoint(Point{5, 2}));
    CHECK( rect.containsPoint(Point{0, 0}));
    CHECK(!rect.containsPoint(Point{11, 2}));
}