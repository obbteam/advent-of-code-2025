//
// Created by Obidkhon Akhmadkhonov on 02/12/2025.
//

#ifndef ADVENT_OF_CODE_2025_PART2_H
#define ADVENT_OF_CODE_2025_PART2_H
#include <vector>

struct Machine {
    std::vector<int> joltages;
    std::vector<std::vector<int>> schematics;
};


class Part2 {
public:
    void solve();

private:
    static long long parseAndSolve(std::vector<std::string> &lines);
    static std::vector<int> getJoltages(const std::string & str);
    static std::vector<std::vector<int>> getSchematics(const std::string & str);
    static long long solveZ3(const Machine& m);
};


#endif //ADVENT_OF_CODE_2025_PART2_H
