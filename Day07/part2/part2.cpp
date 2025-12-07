#include "part2.h"

#include "../common/Utils.h"


long long dp[200][200];

void Part2::solve() {
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    auto lines = AoC::loadInput("input.txt");
    long long result = parseAndSolve(lines);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    printMetaData(Record(2025, 7, 2, result, start, end));
}

long long Part2::parseAndSolve(std::vector<std::string> &lines) {
    long long result = 0;

    for (int i = 0; i < lines.size(); i++) {
        for (int j = 0; j < lines[i].size(); j++) {
            dp[i][j] = -1;
        }
    }

    for (int i = 0; i < lines[0].size(); i++) {
        if (lines[0][i] == 'S') {
            result = moveDown(1, i, lines);
        }
    }

    return result;
}

long long Part2::moveDown(int startRow, int col, const std::vector<std::string> &lines) {
    if (dp[startRow][col] != -1) return dp[startRow][col];
    long long result = 0;

    for (int r = startRow; r < lines.size(); r++) {
        if (lines[r][col] == '^') {
            if (col - 1 >= 0) {
                result += moveDown(r, col - 1, lines);
            }
            if (col + 1 < lines[r].size()) {
                result += moveDown(r, col + 1, lines);
            }
            return dp[startRow][col] = result;
        }

        if (r == lines.size() - 1) {
            return dp[startRow][col] = 1;
        }
    }
    return dp[startRow][col] = 0;
}
