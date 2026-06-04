#include "../include/ShapeManager.hpp"
#include "../include/SVGparser.hpp"
#include "../include/Circle.hpp"
#include "../include/Rect.hpp"
#include "../include/Ellipses.hpp"
#include "../include/Line.hpp"
#include "../include/Polygon.hpp"

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

    if (filename.empty()) {
        std::cout << "No file is currently open. Use 'open <file>' to open an SVG file.\n";
        return;
    }

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

bool ShapeManager::hasOpenFile() const {
    return !filename.empty();
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

void ShapeManager::create(const std::string& type, std::vector<std::string>& args) {

    if (args.empty()) {
        std::cout << "Invalid arguments for creating command.\n";
        return;
    }

    Shape* s = nullptr;

    if (type == "circle") {
        if (args.size() < 4) {
            std::cout << "Error: Invalid arguments. Usage: create circle <cx> <cy> <r> <color>\n";
            return;
        }
        Color c = Color::SVGtoColor(args.back());
        Point p = { std::stod(args[0]), std::stod(args[1]) };
        s = new Circle(p, std::stod(args[2]), c);

    } else if (type == "rectangle") {
        if (args.size() < 5) {
            std::cout << "Error: Invalid arguments. Usage: create rectangle <x> <y> <width> <height> <color>\n";
            return;
        }
        Color c = Color::SVGtoColor(args.back());
        Point p = { std::stod(args[0]), std::stod(args[1]) };
        s = new Rect(p, std::stod(args[2]), std::stod(args[3]), c);

    } else if (type == "ellipse") {
        if (args.size() < 5) {
            std::cout << "Error: Invalid arguments. Usage: create ellipse <cx> <cy> <rx> <ry> <color>\n";
            return;
        }
        Color c = Color::SVGtoColor(args.back());
        Point p = { std::stod(args[0]), std::stod(args[1]) };
        s = new Ellipse(p, std::stod(args[2]), std::stod(args[3]), c);

    } else if (type == "line") {
        if (args.size() < 5) {
            std::cout << "Error: Invalid arguments. Usage: create line <x1> <y1> <x2> <y2> <color>\n";
            return;
        }
        Color c = Color::SVGtoColor(args.back());
        Point start = { std::stod(args[0]), std::stod(args[1]) };
        Point end   = { std::stod(args[2]), std::stod(args[3]) };
        s = new Line(start, end, c);

    } else if (type == "polygon") {
        if (args.size() < 7 || args.size() % 2 == 0) {
            std::cout << "Error: Invalid arguments. Usage: create polygon <x1> <y1> ... <xn> <yn> <color>\n";
            return;
        }
        Color c = Color::SVGtoColor(args.back());
        std::vector<Point> points;
        for (size_t i = 0; i < args.size() - 1; i += 2) {
            points.push_back({ std::stod(args[i]), std::stod(args[i + 1]) });
        }
        s = new Polygon(points, c);

    } else {
        std::cout << "Unsupported shape type: " << type << ". Supported types are: circle, rectangle, ellipse, line, polygon.\n";
        return;
    }

    shapes.push_back(s);
    std::cout << "Successfully created " << type 
              << " (" << shapes.size() << ").\n";
    
}

void ShapeManager::erase(int index) {

    if (!validIndex(index)) {
        std::cout << "Error: Invalid index: " << index << "\n";
        return;
    }
    
    delete shapes[index - 1];
    
    shapes.erase(shapes.begin() + index - 1);
    
    std::cout << "Successfully erased shape at index " << index << ".\n";
}

void ShapeManager::translate(int index, double dx, double dy) {
    if (!validIndex(index)) {
        std::cout << "Error: Invalid index: " << index << "\n";
        return;
    }
    shapes[index - 1]->translate(dx, dy);
    std::cout << "Successfully translated shape at index " << index << ".\n";
}

void ShapeManager::translate(double dx, double dy) {
    for (Shape* s : shapes) {
        s->translate(dx, dy);
    }
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

void ShapeManager::within(const std::string& type, std::vector<std::string>& args) {

    if (type == "rectangle" && args.size() != 4) {
        std::cout << "Usage: within rectangle <x> <y> <width> <height>\n";
        return;
    }

    if (type == "circle" && args.size() != 3) {
        std::cout << "Usage: within circle <cx> <cy> <r>\n";
        return;
    }

    Shape* region = nullptr;

    if (type == "rectangle") {

        Point p = { std::stod(args[0]), std::stod(args[1]) };
        region = new Rect(p, std::stod(args[2]), std::stod(args[3]), BLACK);
        
    } else if (type == "circle") {
        Point p = { std::stod(args[0]), std::stod(args[1]) };
        region = new Circle(p, std::stod(args[2]), BLACK);

    } else {
        std::cout << "within supports only 'rectangle' or 'circle' types.\n";
        return;
    }

    bool found = false;
    for (int i = 0 ; i < (int)shapes.size() ; i++) {
        if (shapes[i]->within(*region)) {
            std::cout << i + 1 << ". ";
            shapes[i]->print(std::cout);
            std::cout << "\n";
            found = true;
        }
    }

    if (!found)
        std::cout << "No figures are located within " << type << "\n";

    delete region;
}