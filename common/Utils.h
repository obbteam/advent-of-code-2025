#ifndef AOCUTILS_H
#define AOCUTILS_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

namespace AoC {
    // Reads a file and returns a vector of lines
    inline std::vector<std::string> loadInput(const std::string& filename) {
        std::vector<std::string> lines;
        std::ifstream file(filename);
        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                lines.push_back(line);
            }
            file.close();
        } else {
            std::cerr << "Unable to open file: " << filename << std::endl;
        }
        return lines;
    }
}

#endif