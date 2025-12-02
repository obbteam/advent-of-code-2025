#include "part2.h"

#include <unordered_set>

#include "../common/Utils.h"


void Part2::solve() {
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    auto line = AoC::loadInput("input.txt");
    long long result = 0;

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    printMetaData(Record(2025, 3, 2, result, start, end));

}
