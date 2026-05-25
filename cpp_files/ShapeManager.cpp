#include "../hpp_files/ShapeManager.hpp"
#include "../hpp_files/SVGparser.hpp"
#include "../hpp_files/Circle.hpp"
#include "../hpp_files/Rectangle.hpp"
#include "../hpp_files/Ellipses.hpp"
#include "../hpp_files/Line.hpp"
#include "../hpp_files/Polygon.hpp"

#include <iostream>
#include <stdexcept>

ShapeManager::ShapeManager() : filename("") {}

ShapeManager::~ShapeManager() {
    for (Shape* s : shapes) delete s;
}

bool ShapeManager::validIndex(int index) const {
    return index >= 1 && index <= (int)shapes.size();
}

void ShapeManager::open(const std::string& file) {
    for (Shape* s : shapes) delete s;
    shapes.clear();

    shapes = SVGParser::load(file);
    filename = file;
    std::cout << "Successfully opened " << filename << " with " << shapes.size() << " shapes.\n";
}

void ShapeManager::close() {
    std::string closedFile = filename;
    for (Shape* s : shapes) delete s;
    shapes.clear();
    filename.clear();
    std::cout << "Successfully closed " << closedFile << ".\n";
}

void ShapeManager::save() {
    if (filename.empty()) {
        std::cout << "No file is currently open. Use 'saveas' to specify a filename.\n";
        return;
    }
    SVGParser::save(filename, shapes);
    std::cout << "Successfully saved " << filename << ".\n";
}

void ShapeManager::saveas(const std::string& file) {
    SVGParser::save(file, shapes);
    filename = file;
    std::cout << "Successfully saved as " << filename << ".\n";
}

void ShapeManager::print() {
    if (shapes.empty()) {
        std::cout << "No shapes to display.\n";
        return;
    }
    for (int i = 0 ; i < (int)shapes.size() ; i++) {
        std::cout << i + 1 << ". ";
        shapes[i]->print(std::cout);
        std::cout << "\n";
    }
}

void ShapeManager::create(const std::string& type,
                          std::vector<std::string>& args) {
    
    Shape* s = nullptr;

    Color c = Color::SVGtoColor(args.back());
    
    if (type == "circle") {
        // circle <cx> <cy> <r> <color>
        Point p = { std::stod(args[0]), std::stod(args[1]) };
        s = new Circle(p, std::stod(args[2]), c);

    } else if (type == "rectangle") {
        // rectangle <x> <y> <width> <height> <color>
        Point p = { std::stod(args[0]), std::stod(args[1]) };
        s = new Rect(p, std::stod(args[2]), std::stod(args[3]), c);

    } else if (type == "ellipse") {
        // ellipse <cx> <cy> <rx> <ry> <color>
        Point p = { std::stod(args[0]), std::stod(args[1]) };
        s = new Ellipse(p, std::stod(args[2]), std::stod(args[3]), c);

    } else if (type == "line") {
        // line <x1> <y1> <x2> <y2> <color>
        Point start = { std::stod(args[0]), std::stod(args[1]) };
        Point end   = { std::stod(args[2]), std::stod(args[3]) };
        s = new Line(start, end, c);

    } else if (type == "polygon") {
        // polygon <n> <x1> <y1> ... <xn> <yn> <color>
        int n = std::stoi(args[0]);
        std::vector<Point> pts;
        for (int i = 0 ; i < n ; i++)
            pts.push_back({ std::stod(args[1 + i*2]),
                            std::stod(args[2 + i*2]) });
        s = new Polygon(pts, c);
    } else {
        std::cout << "Unknown shape type: " << type << "\n";
        return;
    }

    shapes.push_back(s);
    std::cout << "Successfully created " << type 
              << " (" << shapes.size() << ").\n";
}

void ShapeManager::erase(int index) {
    if (!validIndex(index)) {
        std::cout << "Invalid index: " << index << "\n";
        return;
    }
    delete shapes[index - 1];
    shapes.erase(shapes.begin() + index - 1);
    std::cout << "Successfully erased shape at index " << index << ".\n";
}

void ShapeManager::translate(int index, double dx, double dy) {
    if (!validIndex(index)) {
        std::cout << "Invalid index: " << index << "\n";
        return;
    }
    shapes[index - 1]->translate(dx, dy);
    std::cout << "Successfully translated shape at index " << index << ".\n";
}

void ShapeManager::translate(double dx, double dy) {
    for (Shape* s : shapes) s->translate(dx, dy);
    std::cout << "Successfully translated all shapes.\n";
}

void ShapeManager::within(int index) {
    if (!validIndex(index)) {
        std::cout << "Invalid index: " << index << "\n";
        return;
    }
    Shape* container = shapes[index - 1];
    bool found = false;

    for (int i = 0 ; i < (int)shapes.size() ; i++) {
        if (i == index - 1) continue;
        if (shapes[i]->within(*container)) {
            std::cout << i + 1 << ". ";
            shapes[i]->print(std::cout);
            std::cout << "\n";
            found = true;
        }
    }
    if (!found) std::cout << "No shapes are within shape at index " << index << ".\n";
}

