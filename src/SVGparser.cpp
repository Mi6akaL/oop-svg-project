#include "../include/SVGparser.hpp"
#include "../include/Circle.hpp"
#include "../include/Rect.hpp"
#include "../include/Ellipses.hpp"
#include "../include/Line.hpp"
#include "../include/Polygon.hpp"

#include <sstream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <filesystem>

// Helper function : Finds the value of an attribute in an SVG tag string.
// Returns "" if attribute is not found
std::string SVGParser::getAttribute(const std::string& tag, const std::string& attr) {
    
    std::string search = attr + "=\"";
    size_t pos = tag.find(search);
    if (pos == std::string::npos) return "";

    pos += search.length();
    size_t end = tag.find("\"", pos);
    if (end == std::string::npos) return "";

    return tag.substr(pos, end - pos);
}

// Parses a rectangle SVG tag and returns a new Rectangle object
Shape* SVGParser::parseRectangle(const std::string& tag) {
    Point p = {
        std::stod(getAttribute(tag, "x")),
        std::stod(getAttribute(tag, "y"))
    };
    double w = std::stod(getAttribute(tag, "width"));
    double h = std::stod(getAttribute(tag, "height"));
    Color  c = Color::SVGtoColor(getAttribute(tag, "fill"));

    return new Rect(p, w, h, c);
}

Shape* SVGParser::parseCircle(const std::string& tag) {
    Point p = {
        std::stod(getAttribute(tag, "cx")),
        std::stod(getAttribute(tag, "cy"))
    };
    double r = std::stod(getAttribute(tag, "r"));
    Color  c = Color::SVGtoColor(getAttribute(tag, "fill"));

    return new Circle(p, r, c);
}

Shape* SVGParser::parseEllipse(const std::string& tag) {
    Point p = {
        std::stod(getAttribute(tag, "cx")),
        std::stod(getAttribute(tag, "cy"))
    };
    double rx = std::stod(getAttribute(tag, "rx"));
    double ry = std::stod(getAttribute(tag, "ry"));
    Color  c = Color::SVGtoColor(getAttribute(tag, "fill"));

    return new Ellipse(p, rx, ry, c);
}

Shape* SVGParser::parseLine(const std::string& tag) {
    Point start = {
        std::stod(getAttribute(tag, "x1")),
        std::stod(getAttribute(tag, "y1"))
    };
    Point end = {
        std::stod(getAttribute(tag, "x2")),
        std::stod(getAttribute(tag, "y2"))
    };

    std::string colorStr = getAttribute(tag, "stroke");
    if (colorStr.empty()) colorStr = getAttribute(tag, "fill");
    Color c = Color::SVGtoColor(colorStr);

    return new Line(start, end, c);

}

Shape* SVGParser::parsePolygon(const std::string& tag) {
    std::string pointsStr = getAttribute(tag, "points");
    std::vector<Point> pts;

    std::stringstream ss(pointsStr);
    std::string token;
    while (ss >> token) {
        size_t comma = token.find(',');
        if (comma == std::string::npos) continue;
        double x = std::stod(token.substr(0, comma));
        double y = std::stod(token.substr(comma + 1));
        pts.push_back({x, y});
    }

    Color c = Color::SVGtoColor(getAttribute(tag, "fill"));
    return new Polygon(pts, c);
}

std::vector<Shape*> SVGParser::load(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::ofstream create(filename);

        create <<
            R"(<?xml version="1.0" standalone="no"?>
            <svg xmlns="http://www.w3.org/2000/svg">
            </svg>)";
        
        create.close();

        file.open(filename);
    }
        

    std::string content((std::istreambuf_iterator<char>(file)),
                         std::istreambuf_iterator<char>());

    std::vector<Shape*> shapes;
    size_t pos = 0;

    while (pos < content.size()) {
        size_t open = content.find('<', pos);
        if (open == std::string::npos) break;

        size_t close = content.find('>', open);
        if (close == std::string::npos) break;

        std::string tag = content.substr(open, close - open + 1);
        pos = close + 1;

        std::string lower = tag;
        std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

        try {
            if (lower.find("<rect ")    != std::string::npos) shapes.push_back(parseRectangle(tag));
            if (lower.find("<circle ")  != std::string::npos) shapes.push_back(parseCircle(tag));
            if (lower.find("<ellipse ") != std::string::npos) shapes.push_back(parseEllipse(tag));
            if (lower.find("<line ")    != std::string::npos) shapes.push_back(parseLine(tag));
            if (lower.find("<polygon ") != std::string::npos) shapes.push_back(parsePolygon(tag));
        } catch (const std::exception& e) {
            for (Shape* s : shapes)
                delete s;
            
            throw std::runtime_error(std::string("Invalid SVG file: ") + e.what());
        }
    }

    return shapes;
}

void SVGParser::save(const std::string& filename, const std::vector<Shape*>& shapes) {
    std::ofstream file(filename);
    if (!file.is_open())
        throw std::runtime_error("Could not open file: " + filename);

    file << "<?xml version=\"1.0\" standalone=\"no\"?>\n";  
    file << "<svg xmlns=\"http://www.w3.org/2000/svg\">\n";

    for (const Shape* s : shapes)
        file << "  " << s->toSVGtag() << "\n";

    file << "</svg>\n";
    
}



