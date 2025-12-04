#include "part2.h"

#include "../common/Utils.h"


void Part2::solve() {
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    auto lines = AoC::loadInput("input.txt");
    long long result = parseAndSolve(lines);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    printMetaData(Record(2025, 4, 2, result, start, end));
}

long long Part2::parseAndSolve(std::vector<std::string> &lines) {
    long long result = 0;
    bool canRemove = true;
    std::vector<std::pair<int,int>> toRemove;

    while (canRemove) {
        int localCount = 0;
        for (int y = 0; y < lines.size(); y++) {
            for (int x = 0; x < lines[y].size(); x++) {
                if (lines[y][x] == '@') {
                    if (checkDirections(x,y,lines)) {
                        toRemove.emplace_back(x,y);
                        localCount++;
                    }
                }
            }
        }
        removePaper(toRemove, lines);
        toRemove.clear();

        if (localCount == 0)
            canRemove = false;

        result+=localCount;
    }


    return result;
}

bool Part2::checkDirections(int x, int y, std::vector<std::string> &lines) {
    int count = 0;
    for (auto d : directions) {
        int newX = x + d[0];
        int newY = y + d[1];

        if (newX >= 0 && newX < lines.size() && newY >= 0 && newY < lines.size()) {
            if (lines[newY][newX] == '@') {
                count++;
            }
        }
    }

    return count < 4;
};



void Part2::removePaper(std::vector<std::pair<int,int>>& toRemove, std::vector<std::string> &lines) {
    for (auto &[x, y] : toRemove) {
        lines[y][x] = 'x';
    }
    toRemove.clear();
};

