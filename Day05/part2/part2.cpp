#include "part2.h"

#include "../common/Utils.h"


void Part2::solve() {
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    auto lines = AoC::loadInput("input.txt");
    long long result = parseAndSolve(lines);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    printMetaData(Record(2025, 5, 2, result, start, end));
}

long long Part2::parseAndSolve(std::vector<std::string> &lines) {
    long long result = 0;
    std::vector<std::pair<long, long> > ranges;
    int i = 0;
    while (!lines[i].empty()) {
        int idx = lines[i].find_first_of('-');
        ranges.emplace_back(
            std::stol(lines[i].substr(0, idx)),
            std::stol(lines[i].substr(idx + 1))
        );
        i++;
    }

    auto foldedRanges = foldRanges(ranges);

    for (auto range : foldedRanges) {
        result += range.second - range.first + 1;
    }

    return result;
}

std::vector<std::pair<long, long> > Part2::foldRanges(std::vector<std::pair<long, long> > &ranges) {
    std::sort(ranges.begin(), ranges.end());

    std::vector<std::pair<long, long> > result;
    result.push_back(ranges[0]);
    for (int i = 1; i < ranges.size(); ++i) {
        if (ranges[i].first <= result.back().second) {
            result.back().second = std::max(ranges[i].second, result.back().second);
            continue;
        }
        result.push_back(ranges[i]);
    }
    return result;
}
