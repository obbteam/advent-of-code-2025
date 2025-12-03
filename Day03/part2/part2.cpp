#include "part2.h"

#include <unordered_set>

#include "../common/Utils.h"


void Part2::solve() {
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    auto lines = AoC::loadInput("input.txt");
    long long result = parseAndSolve(lines);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    printMetaData(Record(2025, 3, 2, result, start, end));

}


long long Part2::parseAndSolve(std::vector<std::string> &lines) {
    int MIN_LENGTH = 12, l = 0, r = 0;
    long long result = 0;

    for (const auto &line: lines) {
        std::string str;
        int i = 1, prevPos = 0, n = line.length();
        while (i <= MIN_LENGTH) {
            std::string range = line.substr(prevPos, n - prevPos + i - MIN_LENGTH);
            int maxP = 0;
            char maxD = '0';
            for (int j = 0; j < range.length(); j++) {
                // first occurrence of the max digit
                if (range[j] > maxD) {
                    maxD = range[j];
                    maxP = j;
                }
            }
            prevPos += maxP + 1;
            str += maxD;
            i++;
        }
        result+= std::stoll(str);
    }
    return result;
}

