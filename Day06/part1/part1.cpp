#include "part1.h"

#include <numeric>

#include "../common/Utils.h"


void Part1::solve() {
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    auto lines = AoC::loadInput("input.txt");
    long long result = parseAndSolve(lines);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    printMetaData(Record(2025, 6, 1, result, start, end));
}

long long Part1::parseAndSolve(std::vector<std::string> &lines) {
    long long result = 0;
    std::vector<std::pair<char, long long>> signs;
    int lastIndex = lines.size() - 1;
    for (char j : lines[lastIndex]) {
        if (j == '*') signs.emplace_back('*', 1);
        else if (j == '+') signs.emplace_back('+', 0);
    }

    int k = 0;
    for (int i = lines.size() - 2; i >= 0; i--) {
        trimLine(lines[i]);
        std::string s;
        for (int j = 0; j < lines[i].size(); j++) {
            if (lines[i][j] == ' ' && s.empty())
                continue;
            if (lines[i][j] == ' ') {
                if (signs[k].first == '+')
                    signs[k].second += std::stoll(s);
                else if (signs[k].first == '*')
                    signs[k].second *= std::stoll(s);
                k++;
                s.clear();
                continue;
            };
            s += lines[i][j];
        }
        if (signs[k].first == '+')
            signs[k].second += std::stoll(s);
        else if (signs[k].first == '*')
            signs[k].second *= std::stoll(s);
        k=0;
    }

    for (auto [c, sum] : signs)
        result += sum;

    return result;
}

void Part1::trimLine(std::string& s) {
    while (!s.empty() && s.back() == ' ') s.pop_back();
    int i = 0;
    while (!s.empty() && i < s.size()) {
        if (s[i] == ' ') i++;
        else break;
    }

    s = s.substr(i);
}
