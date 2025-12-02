//
// Created by Obidkhon Akhmadkhonov on 02/12/2025.
//

#ifndef ADVENT_OF_CODE_2025_PART1_H
#define ADVENT_OF_CODE_2025_PART1_H
#include <string>


class Part1 {
public:
    void solve();
private:
    static long long parseInputAndSolve(const std::string &line);

    static long long findInvalid(const std::string &left, const std::string &right);
};


#endif //ADVENT_OF_CODE_2025_PART1_H
