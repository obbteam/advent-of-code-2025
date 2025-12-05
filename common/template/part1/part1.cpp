#include "part1.h"

#include "../common/Utils.h"


void Part1::solve() {
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    auto lines = AoC::loadInput("input.txt");
    long long result = parseAndSolve(lines);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    printMetaData(Record(2025, 1, 1, result, start, end));
}

long long Part1::parseAndSolve(std::vector<std::string> &lines) {
    long long result = 0;

    return result;
}
