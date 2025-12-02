//
// Created by Obidkhon Akhmadkhonov on 02/12/2025.
//

#ifndef ADVENT_OF_CODE_2025_PART2_H
#define ADVENT_OF_CODE_2025_PART2_H
#include <string>


class Part2 {
public:
    void solve();

private:
    static std::string makeDuplicate(const std::string &str, int x);

    static long long parseInputAndSolve(const std::string &line);

    static long long findInvalid(const std::string &left, const std::string &right);
};


#endif //ADVENT_OF_CODE_2025_PART2_H
