//
// Created by Obidkhon Akhmadkhonov on 02/12/2025.
//

#include "./part1.h"

#include <chrono>

#include "Utils.h"

void Part1::solve() {
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    auto lines = AoC::loadInput("input.txt");

    int clock = 50, ans = 0;
    for (std::string &line: lines) {
        if (line[0] == 'L') clock -= std::stoi(line.substr(1));
        else if (line[0] == 'R') clock += std::stoi(line.substr(1));

        clock %= 100;

        if (clock < 0)
            clock = 100 - std::abs(clock);
        else if (clock == 0) ans++;
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    printMetaData(Record(2025, 1, 1, ans, start, end));
}
