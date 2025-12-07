#include "part1.h"

#include "../common/Utils.h"


void Part1::solve() {
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    auto lines = AoC::loadInput("input.txt");
    long long result = parseAndSolve(lines);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    printLines(lines);
    printMetaData(Record(2025, 7, 1, result, start, end));
}

long long Part1::parseAndSolve(std::vector<std::string> &lines) {
    long long result = 0;

    for (int i = 0; i < lines[0].size(); i++) {
        if (lines[0][i] == 'S') {
            moveDown(1, i, result, lines);
        }
    }

    return result;
}

void Part1::moveDown(int i, int j, long long& result,std::vector<std::string> &lines) {
    for (; i < lines.size(); i++) {
        if (lines[i][j] == 'X') break;
        if (lines[i][j] == '^') {
            lines[i][j] = 'X';
            if (j - 1 >= 0 && lines[i][j-1] != '|') {
                moveDown(i, j - 1, result, lines);
            }
            if (j + 1 < lines[i].size() && lines[i][j+1] != '|') {
                moveDown(i, j + 1, result, lines);
            }
            result++;
            break;
        }
        lines[i][j] = '|';
    }
}

void Part1::printLines(const std::vector<std::string> &lines) {
    for (auto line: lines) {
        for (auto &c: line) {
            std::cout << c;
        }
        std::cout << '\n';
    }
}