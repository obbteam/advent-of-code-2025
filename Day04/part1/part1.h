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
    long long parseAndSolve(std::vector<std::string> & lines);

    bool checkDirections(int x, int y, std::vector<std::string> &lines);

    std::vector<std::vector<int> > directions = {
        {1, 0},
        {1, 1},
        {0, 1},
        {-1, 1},
        {-1, 0},
        {-1, -1},
        {0, -1},
        {1, -1}
    };
};


#endif //ADVENT_OF_CODE_2025_PART1_H
