//
// Created by Obidkhon Akhmadkhonov on 02/12/2025.
//

#ifndef ADVENT_OF_CODE_2025_PART2_H
#define ADVENT_OF_CODE_2025_PART2_H
#include <vector>


class Part2 {
public:
    void solve();

private:
    long long parseAndSolve(std::vector<std::string> &lines);
    long long getNumbers(int j, const char& sign, const std::vector<std::string> &lines);
};


#endif //ADVENT_OF_CODE_2025_PART2_H
