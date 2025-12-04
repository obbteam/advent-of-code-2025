//
// Created by Obidkhon Akhmadkhonov on 02/12/2025.
//

#ifndef ADVENT_OF_CODE_2025_PART2_H
#define ADVENT_OF_CODE_2025_PART2_H
#include <vector>


class Part2 {
public:
    static void solve();
private:
    static long long parseAndSolve(std::vector<std::string> & lines);

    static bool checkDirections(const int& x, const int& y, const std::vector<std::string> &lines);

    static void removePaper(const std::vector<std::pair<int,int>>& toRemove, std::vector<std::string> &lines);

    static constexpr int directions[8][2] = {
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


#endif //ADVENT_OF_CODE_2025_PART2_H
