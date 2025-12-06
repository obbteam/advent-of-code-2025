#include "part2.h"

#include "../common/Utils.h"


void Part2::solve() {
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    auto lines = AoC::loadInput("input.txt");
    long long result = parseAndSolve(lines);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    printMetaData(Record(2025, 6, 2, result, start, end));
}

long long Part2::parseAndSolve(std::vector<std::string> &lines) {
    long long result = 0;

    int longestLineSize = 0;
    for (const auto & line : lines) {
        longestLineSize = std::max(static_cast<int>(line.size()), longestLineSize);
    }

    for (int i = 0; i < lines[lines.size() - 1].size(); i++) {
        if (lines[lines.size() - 1][i] == '*' || lines[lines.size() - 1][i] == '+')
            result+=getNumbers(i, lines[lines.size() - 1][i], lines, longestLineSize);
    }

    return result;
}

long long Part2::getNumbers(int j, const char& sign, const std::vector<std::string> &lines, int longestLineSize) {
    long long result = sign == '+' ? 0 : 1;
    int nextSignIdx = j+1;
    const std::string& lastLine = lines.back();

    for (;nextSignIdx < longestLineSize; nextSignIdx++) {
        if (nextSignIdx < lastLine.size() && (lastLine[nextSignIdx] == '*' || lastLine[nextSignIdx] == '+'))
            break;
    }

    std::string num;
    for (int k = j; k < nextSignIdx; k++) {
        for (int i = 0; i < lines.size() - 1; i++) {
            if (isdigit(lines[i][k]))
                num += lines[i][k];
        }
        if (sign == '+' && !num.empty())
            result += std::stoll(num);
        else if (!num.empty())
            result *= std::stoll(num);
        num.clear();
    }

    return result;
}
