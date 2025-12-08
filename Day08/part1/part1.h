//
// Created by Obidkhon Akhmadkhonov on 02/12/2025.
//

#ifndef ADVENT_OF_CODE_2025_PART1_H
#define ADVENT_OF_CODE_2025_PART1_H
#include <vector>
#include <Utils.h>
#include <unordered_set>

class Part1 {
public:
    void solve();

private:
    static long long parseAndSolve(std::vector<std::string> &lines);
    static std::vector<Coordinate> getCoordinates(const std::vector<std::string> &lines);
    static long long makeCircuits(const std::vector<Coordinate>& coordinates, int n);
    static long long calculateProductOfTop3(std::vector<std::unordered_set<Coordinate> > & circuits);
};

#endif //ADVENT_OF_CODE_2025_PART1_H
