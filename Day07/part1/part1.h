//
// Created by Obidkhon Akhmadkhonov on 02/12/2025.
//

#ifndef ADVENT_OF_CODE_2025_PART1_H
#define ADVENT_OF_CODE_2025_PART1_H
#include <vector>


class Part1 {
public:
    void solve();

private:
    long long parseAndSolve(std::vector<std::string> &lines);
    void moveDown(int i, int j, long long& result, std::vector<std::string> &lines);
    void printLines(const std::vector<std::string> &lines);
};


#endif //ADVENT_OF_CODE_2025_PART1_H
