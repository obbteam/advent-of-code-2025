#include "part1.h"

#include <unordered_set>

#include "../common/Utils.h"


void Part1::solve() {
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    auto lines = AoC::loadInput("input.txt");
    long long result = parseAndSolve(lines);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    printMetaData(Record(2025, 3, 1, result, start, end));
}

long long Part1::parseAndSolve(std::vector<std::string> &lines) {
    long long result = 0;
    for (const auto &line: lines) {
        char d1 = '0', d2 = '0';
        int localMaxPos = 0;
        for (int i = 0; i < line.size() - 1; i++) {
            if (line[i] > d1) {
                d1 = line[i];
                localMaxPos = i;
            }
        }

        for (int i = localMaxPos + 1; i < line.size(); i++) {
            if (line[i] > d2) {
                d2 = line[i];
            }
        }

        result += (d1 - '0') * 10 + (d2 - '0');
    }

    return result;
}
