#include "part1.h"

#include "../common/Utils.h"


void Part1::solve() {
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    auto lines = AoC::loadInput("input.txt");
    long long result = parseAndSolve(lines);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    printMetaData(Record(2025, 4, 1, result, start, end));
}

long long Part1::parseAndSolve(const std::vector<std::string> &lines) {
    long long result = 0;

    for (int y = 0; y < lines.size(); y++) {
        for (int x = 0; x < lines[y].size(); x++) {
            if (lines[y][x] == '@')
                result+=checkDirections(x,y,lines);
        }
    }

    return result;
}

bool Part1::checkDirections(const int& x, const int& y, const std::vector<std::string> &lines) {
    int count = 0;
    for (auto d : directions) {
        int newX = x + d[0];
        int newY = y + d[1];

        if (newX >= 0 && newX < lines.size() && newY >= 0 && newY < lines.size()) {
            if (lines[newY][newX] == '@') {
                count++;
            }
            if (count >= 4) return false;
        }
    }
    return true;
};
