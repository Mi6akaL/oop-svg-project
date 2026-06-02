#ifndef __SVGPARSER_HPP
#define __SVGPARSER_HPP

#include <string>
#include <vector>
#include "Shape.hpp"


class SVGParser {
    private:
        static std::string getAttribute(const std::string& tag,
                                        const std::string& attr);

        static Shape* parseRectangle(const std::string& tag);
        static Shape* parseCircle   (const std::string& tag);
        static Shape* parseEllipse  (const std::string& tag);
        static Shape* parseLine     (const std::string& tag);
        static Shape* parsePolygon  (const std::string& tag);

    public:

        static std::vector<Shape*> load(const std::string& filename);

        static void save(const std::string& filename, 
                         const std::vector<Shape*>& shapes);
};

#endif