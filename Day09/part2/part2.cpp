#include "part2.h"

#include "../common/Utils.h"


void Part2::solve() {
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    auto lines = AoC::loadInput("input.txt");
    const long long result = parseAndSolve(lines);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    printMetaData(Record(2025, 9, 2, result, start, end));
}

long long Part2::parseAndSolve(std::vector<std::string> &lines) {
    std::vector<Point> points;
    points.reserve(lines.size());

    // make points
    for (auto &line: lines) {
        auto idx = line.find(',');
        points.emplace_back(
            std::stoi(line.substr(0, idx)),
            std::stoi(line.substr(idx + 1))
        );
    }

    long long maxArea = 0;
    // find maxArea
    for (int i = 0; i < points.size(); ++i) {
        for (int j = i + 1; j < points.size(); ++j) {
            maxArea = std::max(maxArea, findArea(points[i], points[j]));
        }
    }

    long long maxX = 0, maxY = 0, minX = INT_MAX, minY = INT_MAX;
    for (auto &p : points) {
        maxX = std::max(maxX, p.x);
        maxY = std::max(maxY, p.y);
        minX = std::min(minX, p.x);
        minY = std::min(minY, p.y);
    }

    std::cout << maxX << " " <<  maxY << " " << minX << " " << minY << std::endl;

    return maxArea;
}
