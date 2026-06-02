#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../include/ColorManager.hpp"

// Компилация: g++ tests/test_colors.cpp src/*.cpp -o tests/run_colors

TEST_CASE("SVGtoColor parses all formats correctly") {
    CHECK(Color::SVGtoColor("red")              == RED);
    CHECK(Color::SVGtoColor("RED")              == RED);
    CHECK(Color::SVGtoColor("#ff0000")          == RED);
    CHECK(Color::SVGtoColor("#f00")             == RED);
    CHECK(Color::SVGtoColor("rgb(255, 0, 0)")   == RED);
    CHECK(Color::SVGtoColor(" rgb(0,0,0) ")     == BLACK);
}

TEST_CASE("colorToSVG produces correct output") {
    CHECK(RED.colorToSVG() == "rgb(255,0,0)");
    CHECK(BLACK.colorToSVG() == "rgb(0,0,0)");
    CHECK(WHITE.colorToSVG() == "rgb(255,255,255)");
}