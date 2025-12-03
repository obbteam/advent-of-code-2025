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
        std::vector<int> prefix(line.size() + 1, 0);
        std::vector<int> sufix(line.size() + 1, 0);

        for (int i = 0; i < line.size(); i++) {
            prefix[i + 1] = std::max(prefix[i], line[i] - '0');
        }

        for (int i = line.length() - 1; i >= 0; --i) {
            sufix[i] = std::max(sufix[i+1], line[i] - '0');
        }

        int localMax = 0;
        for (int i = 1; i < prefix.size() - 1; i++) {
            localMax = std::max(localMax, prefix[i] * 10 + sufix[i]);
        }
        result += localMax;
        std::cout << localMax << std::endl;


    }
    return result;
}
