#include "include/ShapeManager.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

// Helper function to split a string into tokens based on whitespace
std::vector<std::string> tokenize(const std::string& line) {
    std::vector<std::string> tokens;
    std::stringstream ss(line);
    std::string token;
    while (ss >> token) tokens.push_back(token);
    return tokens;
}


bool isNumber(const std::string& s) {
    if (s.empty()) return false;
    for (char c : s) {
        if (!std::isdigit(c)) return false;
    }
    return true;
}

int main() {
    ShapeManager manager;
    std::string line;

    std::cout << "SVG Editor. Type 'help' for a list of commands.\n";

    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, line)) break;

        std::vector<std::string> tokens = tokenize(line);
        if (tokens.empty()) continue;

        std::string cmd = tokens[0];

        if (cmd != "open" && cmd != "help" && cmd != "exit" && !manager.hasOpenFile()) {

            std::cout << "No file is currently open. Use 'open <file>' to open an SVG file.\n";
            continue;
        }

        try {
            if (cmd == "open") {
                if (tokens.size() != 2) { std::cout << "Usage: open <file>\n"; continue; }
                manager.open(tokens[1]);

            } else if (cmd == "close") {
                manager.close();

            } else if (cmd == "save") {
                manager.save();

            } else if (cmd == "saveas") {
                if (tokens.size() != 2) { std::cout << "Usage: saveas <file>\n"; continue; }
                manager.saveas(tokens[1]);

            } else if (cmd == "print") {
                manager.print();

            } else if (cmd == "create") {
                if (tokens.size() < 3) { std::cout << "Usage: create <type> <params...>\n"; continue; }
                std::string type = tokens[1];
                std::vector<std::string> args(tokens.begin() + 2, tokens.end());
                manager.create(type, args);

            } else if (cmd == "erase") {
                if (tokens.size() != 2) { std::cout << "Usage: erase <n>\n"; continue; }
                manager.erase(std::stoi(tokens[1]));

            } else if (cmd == "translate") {

                int index = -1;

                double vertical = 0;
                double horizontal = 0;

                int start = 1;

                if (tokens.size() == 4 && isNumber(tokens[1])) {
                    index = std::stoi(tokens[1]);
                    start = 2;
                }

                for (int i = start; i < (int)tokens.size(); i++) {
                    
                    if (tokens[i].rfind("vertical=", 0) == 0) {
                        vertical = std::stod(tokens[i].substr(9));

                    } else if (tokens[i].rfind("horizontal=", 0) == 0) {
                        horizontal = std::stod(tokens[i].substr(11));
                    }
                }

                if (index == -1) {
                    manager.translate(horizontal, vertical);
                } else {
                    manager.translate(index, horizontal, vertical);
                }


            } else if (cmd == "within") {
                if (tokens.size() < 2) { std::cout << "Usage: within <type> <params...>\n"; continue; }

                if (tokens.size() == 2 && isNumber(tokens[1])) {
                    manager.within(std::stoi(tokens[1]));
                } else {
                    std::string type = tokens[1];
                    std::vector<std::string> args(tokens.begin() + 2, tokens.end());
                    manager.within(type, args);
                }
                

            } else if (cmd == "help") {
                std::cout << "Commands:\n"
                          << "  open <file>                 - Open an SVG file\n"
                          << "  close                       - Close the current file\n"
                          << "  save                        - Save the current file\n"
                          << "  saveas <file>               - Save as a new file\n"
                          << "  print                       - Print all shapes\n"
                          << "  create <type> <params...>   - Create a new shape\n"
                          << "  erase <n>                   - Erase shape at index n\n"
                          << "  translate [<n>] vertical=<dy> horizontal=<dx> - Translate shapes\n"
                          << "  within <type> <params...>   - Find shapes within a region\n"
                          << "  help                        - Show this help message\n"
                          << "  exit                        - Exit the program\n";
            } else if (cmd == "exit") {
                std::cout << "Exiting the program...\n";
                break;

            } else {
                std::cout << "Unknown command: " << cmd << ". Type 'help' for a list of available commands.\n";
            }
    
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
        }  
        
    }

    return 0;
}