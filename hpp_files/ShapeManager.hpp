#ifndef __SHAPEMANAGER_HPP
#define __SHAPEMANAGER_HPP

#include <vector>
#include <string>
#include "Shape.hpp"

class ShapeManager {
    private:
        std::vector<Shape*> shapes;
        std::string filename;

        bool validIndex(int index) const;

    public:
        ShapeManager();
        ~ShapeManager();

        // File operations
        void open   (const std::string& filename);
        void close  ();
        void save   ();
        void saveas (const std::string& filename);

        // Shape operations
        void print     ();
        void create    (const std::string& type, std::vector<std::string>& args);
        void erase     (int index);
        void translate (int index, double dx, double dy);
        void translate (double dx, double dy);
        void within    (int index);
};

#endif