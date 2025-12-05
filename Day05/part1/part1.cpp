#include "part1.h"

#include "../common/Utils.h"


void Part1::solve() {
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    auto lines = AoC::loadInput("input.txt");
    long long result = parseAndSolve(lines);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    printMetaData(Record(2025, 5, 1, result, start, end));
}

long long Part1::parseAndSolve(std::vector<std::string> &lines) {
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
    i++;

    auto foldedRanges = foldRanges(ranges);

    while (i < lines.size()) {
        auto target = std::stol(lines[i]);
        auto it = std::upper_bound(
            foldedRanges.begin(),
            foldedRanges.end(),
            target,
            [](const long &val, const std::pair<long, long> &range) {
                return val < range.first;
            }
        );

        bool is_inside = false;

        if (it != foldedRanges.begin()) {
            auto candidate = std::prev(it);

            if (target <= candidate->second) {
                is_inside = true;
            }
        }

        if (is_inside)
            result++;

        i++;
    }

    return result;
}

std::vector<std::pair<long, long> > Part1::foldRanges(std::vector<std::pair<long, long> > &ranges) {
    std::sort(ranges.begin(), ranges.end());

    std::vector<std::pair<long, long> > result;
    result.push_back(ranges[0]);
    for (int i = 1; i < ranges.size(); ++i) {
        if (ranges[i].first < result.back().second) {
            result.back().second = std::max(ranges[i].second, result.back().second);
            continue;
        }
        result.push_back(ranges[i]);
    }
    return result;
}
