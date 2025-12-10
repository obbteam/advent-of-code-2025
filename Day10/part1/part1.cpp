#include "part1.h"

#include <unordered_set>

#include "LightState.h"
#include "../common/Utils.h"


void Part1::solve() {
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    auto lines = AoC::loadInput("input.txt");
    const long long result = parseAndSolve(lines);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    printMetaData(Record(2025, 10, 1, result, start, end));
}

long long Part1::parseAndSolve(std::vector<std::string> &lines) {
    long long result = 0;

    for (auto &line: lines) {
        size_t sb1 = 0, sb2 = line.find_last_of(']');
        size_t p1 = sb2 + 2, p2 = line.find_last_of(')');
        // size_t cb1 = p2 + 2, cb2 = line.size() - 1;

        auto target = getLightDiagram(line.substr(sb1, sb2 - sb1 + 1));
        auto schematics = getSchematics(line.substr(p1, p2 - p1 + 1));

        result += findMinButtons(target, schematics);
        // auto joltages = getJoltages(line.substr(cb1, cb2 - cb1));
    }

    return result;
}

LightState Part1::getLightDiagram(const std::string &str) {
    LightState lightDiagram;

    for (int i = 0; i < str.size() - 1; i++) {
        if (str[i + 1] == '#') lightDiagram.switches.insert(i);
    }

    return lightDiagram;
}

std::vector<LightState> Part1::getSchematics(const std::string &str) {
    std::vector<LightState> schematics;

    std::unordered_set<int> curSet;
    std::string curNum;
    for (const auto &c: str) {
        if (c == ')') {
            curSet.insert(std::stoi(curNum));
            schematics.emplace_back(curSet);
            curSet.clear();
            curNum.clear();
        } else if (isdigit(c)) {
            curNum.push_back(c);
        } else if (c == ',') {
            curSet.insert(std::stoi(curNum));
            curNum.clear();
        }
    }

    return schematics;
}

int Part1::findMinButtons(const LightState &target, const std::vector<LightState> &schematics) {
    std::unordered_set<LightState> visited;
    std::vector<LightState> currentLevel;

    for (const auto &s : schematics) {
        if (s == target) return 1;
        currentLevel.emplace_back(s);
    }
    int depth = 1;
    while (!currentLevel.empty()) {
        depth++;

        std::vector<LightState> newLevel;
        for (const auto &cur : currentLevel) {
            for (const auto &s : schematics) {
                auto newState = cur - s;

                if (newState == target) return depth;

                if (!visited.contains(newState)) {
                    visited.insert(newState);
                    newLevel.emplace_back(newState);
                }
            }
        }

        currentLevel.swap(newLevel);
    }

    return -1;
};
