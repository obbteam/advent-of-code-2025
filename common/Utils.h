#ifndef AOCUTILS_H
#define AOCUTILS_H

#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <sstream>


namespace AoC {
    // Reads a file and returns a vector of lines
    inline std::vector<std::string> loadInput(const std::string &filename) {
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

struct Record {
    int year = 2025;
    int day;
    int part;
    long long result;
    std::chrono::steady_clock::time_point start;
    std::chrono::steady_clock::time_point end;
};

// 2. Helper to format time (e.g., switches between "ms" and "s")

inline std::string formatTime(double seconds) {
    std::stringstream ss;

    // If it takes less than 1 second, display in milliseconds
    if (seconds < 1.0) {
        // Convert to ms, print with high precision
        ss << std::fixed << std::setprecision(6) << (seconds * 1000.0) << "ms";
    } else {
        // Otherwise display in seconds
        ss << std::fixed << std::setprecision(9) << seconds << "s";
    }
    return ss.str();
}


inline void printMetaData(const Record &rec) {
    std::chrono::duration<double> elapsed = rec.end - rec.start;
    // Define column widths so Header and Data always match
    const int wYear = 6;
    const int wID = 12; // Enough space for "Day-Part:"
    const int wResult = 35; // Wide space to push time to the right
    const int wTime = 15;

    // --- 1. Print Header ---
    std::cout << std::left
            << std::setw(wYear) << "Year"
            << std::setw(wID) << "Day-Part:"
            << std::setw(wResult) << "Result"
            << std::right
            << std::setw(wTime) << "Elapsed time"
            << "\n";

    // --- 2. Prepare Data Strings ---
    // We combine "2" + "-" + "2" + ":" into one string "2-2:"
    // This allows setw(wID) to align the whole block correctly.
    std::string idString = std::to_string(rec.day) + "-" + std::to_string(rec.part) + ":";

    // --- 3. Print Data ---
    std::cout << std::left
            << std::setw(wYear) << rec.year
            << std::setw(wID) << idString // Now this respects the width!
            << std::setw(wResult) << rec.result
            << std::right
            << std::setw(wTime) << formatTime(elapsed.count())
            << "\n";
}

struct Coordinate {
    long long x{};
    long long y{};
    long long z{};

    Coordinate() = default;

    Coordinate(long long x, long long y, long long z) : x(x), y(y), z(z) {}

    bool operator==(const Coordinate &other) const {
        return x == other.x && y == other.y && z == other.z;
    }
};


namespace std {
    template <>
    struct hash<Coordinate> {
        size_t operator()(const Coordinate &c) const {
            size_t h = 17;
            h = h * 31 + std::hash<long long>{}(c.x);
            h = h * 31 + std::hash<long long>{}(c.y);
            h = h * 31 + std::hash<long long>{}(c.z);
            return h;
        }
    };
}

struct Point {
    long long x;
    long long y;
};

 static long long findArea(Point &a, Point &b) {
    return (std::abs(a.x - b.x) + 1 ) *  (std::abs(a.y - b.y) + 1);
}

struct CoordinatesDistance {
    long double distance;
    Coordinate from;
    Coordinate to;

    bool operator<(const CoordinatesDistance &other) const {
        return distance > other.distance;
    }

    void print() const {
        std::cout << "(" << from.x << ", " << from.y << ", " << from.z << ")\n";
        std::cout << "(" << to.x << ", " << to.y << ", " << to.z << ")\n";
        std::cout << "[" << distance << "]\n\n";
    }
};

inline long double calculateDistance(const Coordinate &a, const Coordinate &b) {
    long double dx = a.x - b.x;
    long double dy = a.y - b.y;
    long double dz = a.z - b.z;

    return sqrtl(dx * dx + dy * dy + dz * dz);
};


#endif
