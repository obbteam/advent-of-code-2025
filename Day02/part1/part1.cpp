#include "part1.h"

#include <unordered_set>

#include "../common/Utils.h"


void Part1::solve() {
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    auto line = AoC::loadInput("input.txt");
    long long result = parseInputAndSolve(line[0]);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    printMetaData(Record(2025, 2, 1, result, start, end));
}

long long Part1::findInvalid(const std::string &left, const std::string &right) {
    long long ans = 0;
    for (long long i = stoll(left); i <= std::stoll(right); ++i) {
        std::string str = std::to_string(i);
        auto first = str.substr(0, str.length() / 2);
        auto second = str.substr(str.length() / 2);
        if (first == second)
            ans += i;
    }
    return ans;
}


long long Part1::parseInputAndSolve(const std::string &line) {
    std::string left, right;
    bool r = false;
    long long ans = 0;

    for (const char &c: line) {
        if (c == ',') {
            if (left.length() % 2 == 0 || right.length() % 2 == 0)
                ans += findInvalid(left, right);
            left.clear();
            right.clear();
            r = false;
            continue;
        }
        if (c == '-') {
            r = true;
            continue;
        }

        if (r) right += c;
        else left += c;
    }
    ans += findInvalid(left, right);

    return ans;
}
