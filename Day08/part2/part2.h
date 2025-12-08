//
// Created by Obidkhon Akhmadkhonov on 02/12/2025.
//

#ifndef ADVENT_OF_CODE_2025_PART2_H
#define ADVENT_OF_CODE_2025_PART2_H
#include <vector>
#include <Utils.h>
#include <unordered_set>


class Part2 {
public:
    void solve();

private:
    static long long parseAndSolve(std::vector<std::string> &lines);

    static std::vector<Coordinate> getCoordinates(const std::vector<std::string> &lines);

    static long long makeCircuits(const std::vector<Coordinate> &coordinates);

    static void pushNewCircuit(std::vector<std::unordered_set<Coordinate> > &circuits, CoordinatesDistance &c);

    static void pushToExistingCircuit(
        std::vector<std::unordered_set<Coordinate> > &circuits,
        const CoordinatesDistance &c,
        const int& fromIdx,
        const int& toIdx
    );
};


#endif //ADVENT_OF_CODE_2025_PART2_H
